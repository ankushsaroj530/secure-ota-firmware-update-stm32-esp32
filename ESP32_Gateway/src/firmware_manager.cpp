#include "firmware_manager.h"
#include "sha256.h"
#include "checksum.h"
#include <string.h>
#include "logger.h"
#include "config.h"
/****************************************************
 * Global Variables
 ****************************************************/
uint8_t *FirmwareBuffer = nullptr;

uint32_t FirmwareSize = 0;

String FirmwareFileName = "";


/****************************************************
 * OTA Firmware Header
 ****************************************************/
FirmwareHeader_t FirmwareHeader;


/****************************************************
 * Load Firmware Into RAM
 ****************************************************/
bool Firmware_Load(uint8_t *data, uint32_t size)
{
    if ((data == nullptr) || (size == 0))
    {
        return false;
    }


    Firmware_Clear();


    FirmwareBuffer = (uint8_t *)malloc(size);


    if (FirmwareBuffer == nullptr)
    {
        FirmwareSize = 0;
        return false;
    }


    memcpy(FirmwareBuffer, data, size);


    FirmwareSize = size;


    return true;
}


/****************************************************
 * Create Firmware Header
 ****************************************************/
bool Firmware_CreateHeader(uint32_t version)
{
    Log_Info("Creating Firmware Header");

    if (FirmwareBuffer == nullptr || FirmwareSize == 0)
    {
        Log_Error("Firmware Buffer Empty");
        return false;
    }

    Log_Info("Current FirmwareSize = " + String(FirmwareSize));

    /*--------------------------------------------------
      Fill Header
    --------------------------------------------------*/
    FirmwareHeader.firmwareSize    = FirmwareSize;
    FirmwareHeader.firmwareVersion = version;
    FirmwareHeader.deviceID        = DEVICE_ID;

    /*--------------------------------------------------
      Calculate CRC32
    --------------------------------------------------*/
    FirmwareHeader.firmwareCRC =
        CRC32_CalculateBuffer(FirmwareBuffer, FirmwareSize);

    /*--------------------------------------------------
      Copy Authentication Token
    --------------------------------------------------*/
    memset(FirmwareHeader.authToken, 0, AUTH_TOKEN_SIZE);

    memcpy(FirmwareHeader.authToken,
           AUTH_TOKEN,
           strlen(AUTH_TOKEN));

    /*--------------------------------------------------
      Calculate SHA256
    --------------------------------------------------*/
    sha256(FirmwareBuffer,
           FirmwareSize,
           FirmwareHeader.sha256);

    /*--------------------------------------------------
      Debug Information
    --------------------------------------------------*/
    Log_Info("Header firmwareSize = " +
             String(FirmwareHeader.firmwareSize));

    Log_Info("Header Version = " +
             String(FirmwareHeader.firmwareVersion));

    Log_Info("Header Device ID = " +
             String(FirmwareHeader.deviceID));

    Log_Info("Header CRC32 = 0x" +
             String(FirmwareHeader.firmwareCRC, HEX));

    Serial.print("Header Auth Token : ");
    for (int i = 0; i < AUTH_TOKEN_SIZE; i++)
    {
        Serial.print((char)FirmwareHeader.authToken[i]);
    }
    Serial.println();

    Serial.print("Header SHA256 : ");
    for (int i = 0; i < 32; i++)
    {
        Serial.printf("%02X", FirmwareHeader.sha256[i]);
    }
    Serial.println();

    return true;
}

/****************************************************
 * Free Firmware Buffer
 ****************************************************/
bool Firmware_Clear()
{
    if (FirmwareBuffer != nullptr)
    {
        free(FirmwareBuffer);
        FirmwareBuffer = nullptr;
    }


    FirmwareSize = 0;

    FirmwareFileName = "";


    return true;
}