#include "UART_Update.h"

static UART_HandleTypeDef *uart;

void UART_Update_Init(UART_HandleTypeDef *huart)
{
    uart = huart;
}

HAL_StatusTypeDef UART_WaitForCommand(void)
{
    uint8_t cmd;

    return HAL_UART_Receive(
            uart,
            &cmd,
            1,
            HAL_MAX_DELAY);
}

HAL_StatusTypeDef UART_ReceiveBuffer(uint8_t *buffer,
                                     uint32_t length)
{
    return HAL_UART_Receive(
            uart,
            buffer,
            length,
            HAL_MAX_DELAY);
}
