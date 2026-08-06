#ifndef FIRMWARE_MANAGER_H
#define FIRMWARE_MANAGER_H

#include <Arduino.h>


#define AUTH_TOKEN_SIZE 16


/****************************************************
 * Firmware Header Structure
 ****************************************************/

#pragma pack(push,1)

typedef struct
{
    uint32_t firmwareSize;
    uint32_t firmwareVersion;
    uint32_t firmwareCRC;
    uint32_t deviceID;

    uint8_t authToken[AUTH_TOKEN_SIZE];

    uint8_t sha256[32];

} FirmwareHeader_t;

#pragma pack(pop)



/****************************************************
 * Global Firmware Buffer
 ****************************************************/

extern uint8_t *FirmwareBuffer;

extern uint32_t FirmwareSize;



/****************************************************
 * Firmware File Name
 ****************************************************/

extern String FirmwareFileName;



/****************************************************
 * Firmware Header Object
 ****************************************************/

extern FirmwareHeader_t FirmwareHeader;



/****************************************************
 * Firmware Functions
 ****************************************************/

bool Firmware_Load(uint8_t *data, uint32_t size);

bool Firmware_Clear();

bool Firmware_CreateHeader(uint32_t version);


#endif