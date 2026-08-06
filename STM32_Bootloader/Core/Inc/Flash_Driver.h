#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include "stm32f1xx_hal.h"
#include <stdint.h>


/* Application start address */
/* Application start address */
#define APP_ADDRESS          0x08008000U

/* Flash test address */
#define FLASH_TEST_ADDRESS   0x08007C00U

/* Flash end address (STM32F103C8 128KB Flash) */
#define FLASH_END_ADDRESS    0x08020000U



HAL_StatusTypeDef Flash_Unlock(void);

HAL_StatusTypeDef Flash_Lock(void);


HAL_StatusTypeDef Flash_ErasePage(uint32_t PageAddress);


HAL_StatusTypeDef Flash_WriteWord(uint32_t Address,
                                  uint32_t Data);



HAL_StatusTypeDef Flash_WriteBuffer(uint32_t Address,
                                    uint8_t *Buffer,
                                    uint16_t Length);

HAL_StatusTypeDef Flash_VerifyBuffer(uint32_t Address,
                                     uint8_t *Buffer,
                                     uint16_t Length);



uint32_t Flash_ReadWord(uint32_t Address);



uint8_t Flash_Test(void);


#endif
