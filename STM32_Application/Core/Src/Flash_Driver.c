#include "Flash_Driver.h"


/* Unlock Flash */
HAL_StatusTypeDef Flash_Unlock(void)
{
    return HAL_FLASH_Unlock();
}


/* Lock Flash */
HAL_StatusTypeDef Flash_Lock(void)
{
    return HAL_FLASH_Lock();
}


/*
 * Erase one Flash page
 * STM32F103 page size = 1KB
 */
HAL_StatusTypeDef Flash_ErasePage(uint32_t PageAddress)
{
    FLASH_EraseInitTypeDef erase;
    uint32_t pageError = 0;


    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.PageAddress = PageAddress;
    erase.NbPages = 1;


    return HAL_FLASHEx_Erase(&erase, &pageError);
}



/*
 * Write one 32-bit word
 */
HAL_StatusTypeDef Flash_WriteWord(uint32_t Address, uint32_t Data)
{

    HAL_StatusTypeDef status;


    /*
     * STM32F103 supports half-word programming.
     * So write lower 16-bit and upper 16-bit separately.
     */

    status = HAL_FLASH_Program(
                FLASH_TYPEPROGRAM_HALFWORD,
                Address,
                (uint16_t)(Data & 0xFFFF)
             );


    if(status != HAL_OK)
        return status;



    status = HAL_FLASH_Program(
                FLASH_TYPEPROGRAM_HALFWORD,
                Address + 2,
                (uint16_t)((Data >> 16) & 0xFFFF)
             );


    return status;
}




/*
 * Write firmware buffer into Flash
 *
 * Address:
 * starting flash address
 *
 * Buffer:
 * received UART packet
 *
 * Length:
 * packet size in bytes
 */
HAL_StatusTypeDef Flash_WriteBuffer(uint32_t Address,
                                    uint8_t *Buffer,
                                    uint16_t Length)
{

    HAL_StatusTypeDef status;


    for(uint16_t i = 0; i < Length; i += 2)
    {

        uint16_t data = 0xFFFF;


        /*
         * Combine two bytes
         */
        data = Buffer[i];


        if((i + 1) < Length)
        {
            data |= ((uint16_t)Buffer[i+1] << 8);
        }



        status = HAL_FLASH_Program(
                    FLASH_TYPEPROGRAM_HALFWORD,
                    Address + i,
                    data
                 );


        if(status != HAL_OK)
        {
            return status;
        }

    }


    return HAL_OK;
}




/*
 * Read Flash word
 */
uint32_t Flash_ReadWord(uint32_t Address)
{
    return *(volatile uint32_t*)Address;
}




/*
 * Flash Driver Test
 *
 * Used only during testing
 */
uint8_t Flash_Test(void)
{

    uint32_t data;


    if(Flash_Unlock() != HAL_OK)
        return 1;



    if(Flash_ErasePage(FLASH_TEST_ADDRESS) != HAL_OK)
    {
        Flash_Lock();
        return 2;
    }



    if(Flash_WriteWord(
            FLASH_TEST_ADDRESS,
            0x12345678) != HAL_OK)
    {
        Flash_Lock();
        return 3;
    }



    data = Flash_ReadWord(FLASH_TEST_ADDRESS);



    Flash_Lock();



    if(data != 0x12345678)
        return 4;



    return 0;
}


HAL_StatusTypeDef Flash_VerifyBuffer(uint32_t Address,
                                     uint8_t *Buffer,
                                     uint16_t Length)
{
    for(uint16_t i = 0; i < Length; i++)
    {
        if(*(volatile uint8_t *)(Address + i) != Buffer[i])
        {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}
