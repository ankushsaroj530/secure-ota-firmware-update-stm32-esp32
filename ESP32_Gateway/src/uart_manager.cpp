#include "uart_manager.h"
#include "config.h"
#include "logger.h"

HardwareSerial STM32Serial(2);

/*----------------------------------------------------------
    Initialize UART
----------------------------------------------------------*/
void UART_Init()
{
    STM32Serial.begin(
        UART_BAUDRATE,
        SERIAL_8N1,
        UART_RX_PIN,
        UART_TX_PIN);

    delay(100);

    UART_ClearBuffer();

    Log_Info("UART Initialized");
}

/*----------------------------------------------------------
    Clear UART RX Buffer
----------------------------------------------------------*/
void UART_ClearBuffer()
{
    while (STM32Serial.available())
    {
        STM32Serial.read();
    }
}

/*----------------------------------------------------------
    Send One Byte
----------------------------------------------------------*/
void UART_SendByte(uint8_t data)
{
    STM32Serial.write(data);
    STM32Serial.flush();
}

/*----------------------------------------------------------
    Send Buffer
----------------------------------------------------------*/
void UART_SendBuffer(const uint8_t *buffer, uint16_t length)
{
    STM32Serial.write(buffer, length);
    STM32Serial.flush();
}

/*----------------------------------------------------------
    Send Command
----------------------------------------------------------*/
/*----------------------------------------------------------
    Send Command
----------------------------------------------------------*/
void UART_SendCommand(uint8_t cmd)
{
    Serial.print("Sending command: 0x");
    Serial.println(cmd, HEX);

    STM32Serial.write(cmd);

    STM32Serial.flush();

    delay(1);
}

/*----------------------------------------------------------
    Read One Line
----------------------------------------------------------*/
String UART_ReadLine(uint32_t timeout)
{
    String line = "";

    unsigned long start = millis();

    while (millis() - start < timeout)
    {
        while (STM32Serial.available())
        {
            char c = STM32Serial.read();

            if (c == '\r')
                continue;

            if (c == '\n')
            {
                if (line.length() > 0)
                    return line;

                continue;
            }

            // Ignore non printable characters
            if (c >= 32 && c <= 126)
            {
                line += c;
            }
        }

        delay(1);
    }

    return line;
}

/*----------------------------------------------------------
    Wait for ACK
----------------------------------------------------------*/
bool UART_WaitACK(uint32_t timeout)
{
    unsigned long start = millis();

    while (millis() - start < timeout)
    {
        String response = UART_ReadLine(300);

        response.trim();

        if (response.length() == 0)
            continue;

        Log_Info("STM32 : " + response);

        if (response.startsWith("ACK"))
            return true;
    }

    return false;
}

bool UART_Send(uint8_t *data, uint16_t length)
{
    if (data == nullptr || length == 0)
        return false;

    STM32Serial.write(data, length);
    STM32Serial.flush();

    return true;
}