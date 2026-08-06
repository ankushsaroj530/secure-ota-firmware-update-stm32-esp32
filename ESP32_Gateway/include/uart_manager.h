#ifndef UART_MANAGER_H
#define UART_MANAGER_H

#include <Arduino.h>
extern HardwareSerial STM32Serial;

bool UART_Send(uint8_t *data, uint16_t length);
/* Initialize UART */
void UART_Init();

/* Clear UART RX buffer */
void UART_ClearBuffer();

/* Send one byte */
void UART_SendByte(uint8_t data);

/* Send multiple bytes */
void UART_SendBuffer(const uint8_t *buffer, uint16_t length);

/* Send command byte */
void UART_SendCommand(uint8_t cmd);

/* Read one line terminated by '\n' */
String UART_ReadLine(uint32_t timeout);

/* Wait for ACK from STM32 */
bool UART_WaitACK(uint32_t timeout);

#endif