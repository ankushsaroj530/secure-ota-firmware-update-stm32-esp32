#include "Protocol.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart1;

/* Packet Buffer */
uint8_t PacketBuffer[PACKET_SIZE];


/* Firmware Header */
extern FirmwareHeader_t gFirmwareHeader;


/*----------------------------------------------------------*/
/* Send String Message */
/*----------------------------------------------------------*/
static void Protocol_SendString(char *msg)
{
    HAL_UART_Transmit(&huart1,
                      (uint8_t *)msg,
                      strlen(msg),
                      HAL_MAX_DELAY);
}


/*----------------------------------------------------------*/
/* Send ACK */
/*----------------------------------------------------------*/
void Protocol_SendACK(void)
{
    Protocol_SendString("ACK\r\n");
}


/*----------------------------------------------------------*/
/* Send NACK */
/*----------------------------------------------------------*/
void Protocol_SendNACK(void)
{
    Protocol_SendString("NACK\r\n");
}


/*----------------------------------------------------------*/
/* Send Bootloader Ready */
/*----------------------------------------------------------*/
void Protocol_SendBootloaderReady(void)
{
    Protocol_SendString("BOOTLOADER READY\r\n");
}


/*----------------------------------------------------------*/
/* Send Installed Firmware Version */
/*----------------------------------------------------------*/
void Protocol_SendInstalledVersion(uint32_t version)
{
    char msg[40];

    sprintf(msg,
            "VERSION:%lu\r\n",
            (unsigned long)version);


    Protocol_SendString(msg);
}


/*----------------------------------------------------------*/
/* Receive Firmware Header */
/*----------------------------------------------------------*/
HAL_StatusTypeDef Protocol_ReceiveHeader(void)
{
    HAL_StatusTypeDef status;


    char msg[128];


    /*
     * Inform ESP32 that STM32 is waiting
     */
    Protocol_SendString(
        "Waiting for Firmware Header...\r\n"
    );


    /*
     * Receive binary header
     *
     * Expected size:
     * sizeof(FirmwareHeader_t) = 64 bytes
     */
    status = HAL_UART_Receive(
                &huart1,
                (uint8_t *)&gFirmwareHeader,
                sizeof(FirmwareHeader_t),
                10000
            );


    if(status != HAL_OK)
    {
        sprintf(msg,
                "Header Receive Failed : %d\r\n",
                status);

        Protocol_SendString(msg);


        Protocol_SendNACK();

        return status;
    }



    /*
     * Print received header information
     */
    sprintf(msg,
            "Header Received\r\n"
            "Size      : %lu\r\n"
            "Version   : %lu\r\n"
            "CRC       : 0x%08lX\r\n"
            "Device ID : %lu\r\n",
            (unsigned long)gFirmwareHeader.firmwareSize,
            (unsigned long)gFirmwareHeader.firmwareVersion,
            (unsigned long)gFirmwareHeader.firmwareCRC,
            (unsigned long)gFirmwareHeader.deviceID);


    Protocol_SendString(msg);



    /*
     * Header accepted
     */
    Protocol_SendACK();


    return HAL_OK;
}


/*----------------------------------------------------------*/
/* Receive Firmware Packet */
/*----------------------------------------------------------*/
HAL_StatusTypeDef Protocol_ReceivePacket(uint16_t length)
{
    char msg[64];

    sprintf(msg, "Receiving %u bytes\r\n", length);
    Protocol_SendString(msg);

    if(length == 0 || length > PACKET_SIZE)
    {
        Protocol_SendString("Invalid Length\r\n");
        return HAL_ERROR;
    }

    return HAL_UART_Receive(
            &huart1,
            PacketBuffer,
            length,
            10000);
}

/*----------------------------------------------------------*/
/* Flush any leftover bytes sitting in the RX stream.
 * Call this after ANY parse failure so garbage/leftover
 * bytes from a desynced packet don't get misread as the
 * next command.
 *----------------------------------------------------------*/
void Protocol_FlushRx(void)
{
    uint8_t junk;

    while(HAL_UART_Receive(&huart1, &junk, 1, 20) == HAL_OK)
    {
        /* keep draining until the line goes quiet for 20ms */
    }

    __HAL_UART_CLEAR_OREFLAG(&huart1);
    __HAL_UART_CLEAR_FEFLAG(&huart1);
    __HAL_UART_CLEAR_NEFLAG(&huart1);
}

/*----------------------------------------------------------*/
/* CRC16-CCITT (poly 0x1021), bitwise, no table needed.
 * Must match EXACTLY on both STM32 and ESP32 sides.
 *----------------------------------------------------------*/
uint16_t Protocol_CRC16(const uint8_t *data, uint32_t length, uint16_t crc)
{
    for(uint32_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)data[i] << 8;

        for(uint8_t j = 0; j < 8; j++)
        {
            if(crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }

    return crc;
}
