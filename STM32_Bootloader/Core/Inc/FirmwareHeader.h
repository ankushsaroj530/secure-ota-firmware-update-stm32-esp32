#ifndef FIRMWAREHEADER_H
#define FIRMWAREHEADER_H

#include "stm32f1xx_hal.h"
#define AUTH_TOKEN_SIZE 16

typedef struct
{
    uint32_t firmwareSize;        // 4 bytes
    uint32_t firmwareVersion;     // 4 bytes
    uint32_t firmwareCRC;         // 4 bytes
    uint32_t deviceID;             // 4 bytes
    uint8_t authToken[16];         // 16 bytes
    uint8_t sha256[32];             // 32 bytes

} FirmwareHeader_t;
/* Declare the global variable */
extern FirmwareHeader_t gFirmwareHeader;

#endif /* FIRMWAREHEADER_H */
