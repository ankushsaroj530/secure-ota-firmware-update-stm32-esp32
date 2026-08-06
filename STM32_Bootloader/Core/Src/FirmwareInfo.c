#include "FirmwareInfo.h"
#include "Flash_Driver.h"

void FirmwareInfo_Load(FirmwareInfo_t *info)
{
    FirmwareInfo_t *flash =
        (FirmwareInfo_t *)FW_INFO_ADDRESS;

    *info = *flash;
}


HAL_StatusTypeDef FirmwareInfo_Save(FirmwareInfo_t *info)
{
    uint32_t address = FW_INFO_ADDRESS;

    if (Flash_Unlock() != HAL_OK)
        return HAL_ERROR;

    if (Flash_ErasePage(FW_INFO_ADDRESS) != HAL_OK)
    {
        Flash_Lock();
        return HAL_ERROR;
    }

    if (Flash_WriteWord(address, info->version) != HAL_OK)
    {
        Flash_Lock();
        return HAL_ERROR;
    }
    address += 4;

    if (Flash_WriteWord(address, info->crc) != HAL_OK)
    {
        Flash_Lock();
        return HAL_ERROR;
    }
    address += 4;

    if (Flash_WriteWord(address, info->deviceID) != HAL_OK)
    {
        Flash_Lock();
        return HAL_ERROR;
    }
    address += 4;

    if (Flash_WriteWord(address, info->reserved) != HAL_OK)
    {
        Flash_Lock();
        return HAL_ERROR;
    }

    Flash_Lock();

    return HAL_OK;
}
