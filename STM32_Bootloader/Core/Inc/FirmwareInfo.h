#ifndef FIRMWAREINFO_H
#define FIRMWAREINFO_H

#include "stm32f1xx_hal.h"

#define FW_INFO_ADDRESS       0x0800F800U

#define UPDATE_FLAG_CLEAR     0xFFFFFFFFU
#define UPDATE_FLAG_REQUEST   0xA55AA55AU

typedef struct
{
    uint32_t version;
    uint32_t crc;
    uint32_t deviceID;

    uint32_t reserved;  /* Use this as the update flag */
} FirmwareInfo_t;

HAL_StatusTypeDef FirmwareInfo_Save(FirmwareInfo_t *info);
void FirmwareInfo_Load(FirmwareInfo_t *info);

#endif
