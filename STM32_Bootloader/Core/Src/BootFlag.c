#include "main.h"
#include "BootFlag.h"

void BootFlag_Init(void)
{
    /* Enable access to STM32F1 backup-domain registers. */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();

    HAL_PWR_EnableBkUpAccess();
}

uint16_t BootFlag_Read(void)
{
    return (uint16_t)BKP->DR1;
}

uint8_t BootFlag_IsUpdateRequested(void)
{
    return (BootFlag_Read() == BOOT_FLAG_UPDATE_REQUEST) ? 1U : 0U;
}

void BootFlag_SetUpdateRequest(void)
{
    BKP->DR1 = BOOT_FLAG_UPDATE_REQUEST;
}

void BootFlag_Clear(void)
{
    BKP->DR1 = 0U;
}
