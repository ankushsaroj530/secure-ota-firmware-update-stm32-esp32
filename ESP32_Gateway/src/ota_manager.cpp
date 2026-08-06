#include "ota_manager.h"
#include "uart_manager.h"
#include "logger.h"
#include "firmware_manager.h"
#include "http_client.h"
#include <esp_task_wdt.h>
#define CMD_EXIT 0x05
/*====================================================
                Global Variables
====================================================*/

OTA_State CurrentState = OTA_IDLE;

static uint32_t InstalledVersion = 0;
static uint32_t ServerVersion = 155;      // Temporary


uint16_t OTA_CRC16(const uint8_t *data, uint32_t length, uint16_t crc)
{
    for (uint32_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)data[i] << 8;

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }

    return crc;
}

/*====================================================
                Check STM32 Version
====================================================*/
bool OTA_CheckVersion()
{
    CurrentState = OTA_CHECK_VERSION;

    Log_Info("Requesting STM32 Version...");

    UART_ClearBuffer();

    UART_SendCommand(0x04);

    unsigned long start = millis();

    while (millis() - start < 3000)
    {
        String response = UART_ReadLine(500);

        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("Response : " + response);

        if (response == "APPLICATION STARTED")
            continue;

        if (response == "BOOTLOADER READY")
            continue;

        if (!response.startsWith("VERSION:"))
            continue;

        InstalledVersion = response.substring(8).toInt();

        Log_Info("Installed Version : " + String(InstalledVersion));
        Log_Info("Server Version : " + String(ServerVersion));

        if (InstalledVersion >= ServerVersion)
            Log_Info("Already Latest Firmware");
        else
            Log_Info("New Firmware Available");

        return true;
    }

    Log_Error("Version Timeout");

    CurrentState = OTA_FAILED;

    return false;
}

/*====================================================
                Request Bootloader
====================================================*/
bool OTA_RequestBootloader()
{
    CurrentState = OTA_ENTER_BOOTLOADER;

    Log_Info("Requesting STM32 Bootloader...");

    UART_ClearBuffer();

    UART_SendCommand(0x55);

    unsigned long start = millis();

    while (millis() - start < 3000)
    {
        String response = UART_ReadLine(500);

        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("STM32 Response : " + response);

        if (response == "APPLICATION STARTED")
            continue;

        if (response == "BOOTLOADER READY")
            continue;

        if (response.startsWith("VERSION:"))
            continue;

        if (response.startsWith("ACK"))
        {
            Log_Info("Bootloader Request Accepted");
            return true;
        }
    }

    Log_Error("Bootloader Request Timeout");

    CurrentState = OTA_FAILED;

    return false;
}

/*====================================================
                Wait Bootloader
====================================================*/
bool OTA_WaitBootloader()
{
    CurrentState = OTA_WAIT_BOOTLOADER;

    Log_Info("Waiting for Bootloader...");

    unsigned long start = millis();

    while (millis() - start < 5000)
    {
        String response = UART_ReadLine(500);

        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("Bootloader : " + response);

        if (response.indexOf("BOOTLOADER READY") >= 0 ||
            response.indexOf("BOOTLOADER_READY") >= 0)
        {
            Log_Info("Bootloader detected");
            return true;
        }
    }

    Log_Error("Bootloader Timeout");

    CurrentState = OTA_FAILED;

    return false;
}



/*====================================================
                Send Header
====================================================*/
bool OTA_SendHeader()
{
    CurrentState = OTA_SEND_HEADER;

    Log_Info("Sending Firmware Header...");

    Log_Info("Firmware Size : " + String(FirmwareHeader.firmwareSize));
    Log_Info("Header Size   : " + String(sizeof(FirmwareHeader)));

    if (!UART_Send((uint8_t *)&FirmwareHeader, sizeof(FirmwareHeader)))
    {
        Log_Error("Header Send Failed");
        return false;
    }

    Log_Info("Waiting Header ACK...");

    unsigned long start = millis();

    while (millis() - start < 10000)
    {
        String response = UART_ReadLine(1000);
        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("STM32 : " + response);

        if (response == "ACK")
        {
            Log_Info("Header Accepted");
            break;
        }

        if (response == "NACK")
        {
            Log_Error("Header Rejected");
            return false;
        }
    }

    Log_Info("Waiting Flash Erase...");

    start = millis();

    while (millis() - start < 10000)
    {
        String response = UART_ReadLine(1000);
        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("STM32 : " + response);

        if (response == "ACK")
        {
            Log_Info("Flash Erase Complete");
            return true;
        }

        if (response == "NACK")
        {
            Log_Error("Flash Erase Failed");
            return false;
        }
    }

    Log_Error("Flash Erase Timeout");
    return false;
}

/*====================================================
                Send Firmware
====================================================*/
bool OTA_SendFirmware()
{
    CurrentState = OTA_SEND_DATA;

    Log_Info("Sending Firmware Data...");

    if (FirmwareBuffer == nullptr || FirmwareSize == 0)
    {
        Log_Error("Firmware Buffer Empty");
        return false;
    }

    const uint16_t CHUNK_SIZE = 256;
    const int MAX_RETRIES = 3;

    uint32_t offset = 0;

    while (offset < FirmwareSize)
    {
        /* Feed the watchdog at the top of every packet iteration. With
         * many packets each doing several blocking UART reads (up to
         * 5s per ACK wait, x3 retries), a large firmware image could
         * otherwise accumulate enough blocking time between resets to
         * trip the task watchdog mid-transfer. */
        esp_task_wdt_reset();

        uint16_t sendSize =
            min((uint32_t)CHUNK_SIZE, FirmwareSize - offset);

        Serial.println();
        Serial.print("Offset = ");
        Serial.println(offset);
        Serial.print("Sending bytes = ");
        Serial.println(sendSize);

        //------------------------------------------
        // Build packet ONCE: cmd + lenLo + lenHi + payload + CRC16(2 bytes)
        //------------------------------------------
        uint8_t packet[CHUNK_SIZE + 5];   // +5: cmd+lenLo+lenHi+payload+crcHi+crcLo

        packet[0] = 'D';
        packet[1] = (uint8_t)(sendSize & 0xFF);
        packet[2] = (uint8_t)((sendSize >> 8) & 0xFF);

        memcpy(&packet[3], FirmwareBuffer + offset, sendSize);

        uint16_t crc = OTA_CRC16(&packet[1], 2, 0xFFFF);      // over lenLo, lenHi
        crc = OTA_CRC16(&packet[3], sendSize, crc);            // over payload

        packet[3 + sendSize] = (uint8_t)(crc >> 8);    // CRC high byte first
        packet[4 + sendSize] = (uint8_t)(crc & 0xFF);  // CRC low byte

        uint16_t packetLen = sendSize + 5;   // <-- update everywhere this is used

        Serial.printf("Packet Header : %02X %02X %02X (crc %04X)\n",
                      packet[0], packet[1], packet[2], crc);

        //------------------------------------------
        // Send with retry — reuses the SAME packet buffer/length every time
        //------------------------------------------
        bool ackReceived = false;
        int retries = 0;

        while (retries < MAX_RETRIES && !ackReceived)
        {
            esp_task_wdt_reset();

            UART_ClearBuffer();   // drop any stale bytes before this attempt

            size_t written = STM32Serial.write(packet, packetLen);
            STM32Serial.flush();

            if (written != packetLen)
            {
                Log_Error("UART Write Failed");
                return false;
            }

            bool gotResponse = false;
            unsigned long start = millis();

            while (millis() - start < 5000)
            {
                String line = UART_ReadLine(500);
                line.trim();

                if (line.length() == 0)
                    continue;

                Log_Info("STM32 : " + line);

                if (line == "ACK")
                {
                    ackReceived = true;
                    gotResponse = true;
                    break;
                }

                if (line == "NACK")
                {
                    gotResponse = true;
                    break;
                }
            }

            if (!gotResponse)
            {
                Log_Error("Packet ACK/NACK Timeout");
                retries++;
                continue;
            }

            if (!ackReceived)
            {
                retries++;
                if (retries < MAX_RETRIES)
                {
                    Log_Warning("Packet rejected, retrying (" +
                                String(retries) + "/" + String(MAX_RETRIES) + ")");
                    delay(100);
                }
            }
        }

        if (!ackReceived)
        {
            Log_Error("Packet Rejected After Retries");
            return false;
        }

        offset += sendSize;

        int percent = (offset * 100) / FirmwareSize;
        Log_Info("Firmware Transfer : " + String(percent) + "%");

        delay(5);   // slightly longer inter-packet gap
    }

    Log_Info("Firmware Data Sent");
    return true;
}

/*====================================================
                Send END
====================================================*/
bool OTA_SendEnd()
{
    CurrentState = OTA_SEND_END;

    Log_Info("Sending END Command...");

    UART_SendCommand('E');

    unsigned long start = millis();

    while (millis() - start < 10000)
    {
        String response = UART_ReadLine(500);
        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("STM32 : " + response);

        if (response == "ACK")
        {
            Log_Info("OTA Update Completed");
            return true;
        }

        if (response == "NACK")
        {
            Log_Error("OTA Update Failed");
            return false;
        }
    }

    Log_Error("END ACK Timeout");

    return false;
}


bool OTA_StartUpdate()
{
    Log_Info("######## NEW OTA START UPDATE ########");
    CurrentState = OTA_IDLE;


    /*
     * Step 1: Check firmware version
     */
    if(!OTA_CheckVersion())
    {
        Log_Error("Version Check Failed");
        return false;
    }


    if(InstalledVersion >= ServerVersion)
    {
        Log_Info("Firmware Already Latest");

        CurrentState = OTA_SUCCESS;
        return true;
    }



    /*
     * Step 2: Download Firmware
     *
     * FirmwareSize will become 8028 here
     */
    Log_Info("Downloading Firmware...");


    if(!HTTP_DownloadFirmware(FirmwareFileName))
    {
        Log_Error("Firmware Download Failed");
        CurrentState = OTA_FAILED;
        return false;
    }



    Log_Info(
        "Downloaded Firmware Size : "
        + String(FirmwareSize)
    );



    /*
     * Step 3: Create Header AFTER download
     */
    Log_Info("Creating Firmware Header...");


    if(!Firmware_CreateHeader(ServerVersion))
    {
        Log_Error("Firmware Header Creation Failed");
        CurrentState = OTA_FAILED;
        return false;
    }


    Log_Info(
        "Prepared Header Size : "
        + String(FirmwareHeader.firmwareSize)
    );



    /*
     * Step 4: Request STM32 Bootloader
     */
    if(!OTA_RequestBootloader())
    {
        return false;
    }


    delay(1500);



    /*
     * Step 5: Wait Bootloader Ready
     */
    if(!OTA_WaitBootloader())
    {
        return false;
    }



    /*
     * Step 6: Send Firmware Header
     */
    if(!OTA_SendHeader())
    {
        return false;
    }



    /*
     * Step 7: Send Firmware Data
     */
    if(!OTA_SendFirmware())
    {
        return false;
    }



    /*
     * Step 8: Send END command
     */
    if(!OTA_SendEnd())
    {
        return false;
    }



    CurrentState = OTA_SUCCESS;


    Log_Info("==============================");
    Log_Info(" OTA UPDATE SUCCESS ");
    Log_Info("==============================");


    return true;
}

/*====================================================
                Getters
====================================================*/

uint32_t OTA_GetInstalledVersion()
{
    return InstalledVersion;
}

uint32_t OTA_GetServerVersion()
{
    return ServerVersion;
}

void OTA_SetServerVersion(uint32_t version)
{
    ServerVersion = version;
}

bool OTA_SendExit()
{
    Log_Info("Sending EXIT Command...");

    UART_ClearBuffer();
    UART_SendCommand(CMD_EXIT);   // 0x05

    unsigned long start = millis();

    while (millis() - start < 5000)
    {
        String response = UART_ReadLine(500);
        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("STM32 : " + response);

        if (response == "ACK")
        {
            Log_Info("STM32 Exiting to Application");
            return true;
        }
    }

    Log_Error("EXIT ACK Timeout");
    return false;
}