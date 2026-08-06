#include "BootManager.h"
#include "FirmwareInfo.h"
#include "stm32f1xx_hal.h"

#include <stdio.h>
#include <stdint.h>

#define APP_ADDRESS  0x08008000U
#define APP_END      FW_INFO_ADDRESS



uint8_t Bootloader_IsUpdateRequested(void)
{
    FirmwareInfo_t info;

    FirmwareInfo_Load(&info);

    return (info.reserved == UPDATE_FLAG_REQUEST);
}




void Bootloader_JumpToApplication(void)
{
    uint32_t appStack = *(volatile uint32_t *)APP_ADDRESS;
    uint32_t appEntry = *(volatile uint32_t *)(APP_ADDRESS + 4U);

    typedef void (*pFunction)(void);

    printf("Jumping...\r\n");
    printf("MSP : 0x%08lX\r\n", appStack);
    printf("RST : 0x%08lX\r\n", appEntry);

    if ((appStack & 0x2FFE0000U) != 0x20000000U)
    {
        printf("Invalid MSP\r\n");
        return;
    }

    if (((appEntry & 1U) == 0U) ||
        ((appEntry & ~1U) < APP_ADDRESS) ||
        ((appEntry & ~1U) >= APP_END))
    {
        printf("Invalid reset handler\r\n");
        return;
    }

    __disable_irq();

    SysTick->CTRL = 0U;
    SysTick->LOAD = 0U;
    SysTick->VAL  = 0U;

    for (uint32_t i = 0U; i < 2U; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFFU;
        NVIC->ICPR[i] = 0xFFFFFFFFU;
    }

    SCB->VTOR = APP_ADDRESS;
    __DSB();
    __ISB();

    __set_MSP(appStack);
    __enable_irq();

    ((pFunction)appEntry)();

    while (1)
    {
    }
}


