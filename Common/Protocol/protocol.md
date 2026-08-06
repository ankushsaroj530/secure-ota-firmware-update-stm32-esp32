Secure OTA UART Protocol

------------------------------------------------

CMD_GET_VERSION (0x04)

ESP32 -----> STM32

STM32 -----> VERSION:131


------------------------------------------------

CMD_ENTER_BOOTLOADER (0x55)

ESP32 -----> STM32

STM32 -----> ACK

STM32 -----> Reset


------------------------------------------------

CMD_UPDATE ('U')

ESP32 -----> Bootloader

Bootloader -----> ACK


------------------------------------------------

HEADER

ESP32 -----> Header

Bootloader -----> ACK

Bootloader -----> ACK


------------------------------------------------

CMD_DATA ('D')

ESP32 -----> Packet

Bootloader -----> ACK


------------------------------------------------

CMD_END ('E')

ESP32 -----> END

Bootloader -----> ACK

Bootloader -----> Verify

Bootloader -----> Jump Application