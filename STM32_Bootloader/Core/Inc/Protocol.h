#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "stm32f1xx_hal.h"
#include "FirmwareHeader.h"


#define PACKET_SIZE    256
#define CMD_EXIT    0x05
/* Global firmware header */
extern FirmwareHeader_t gFirmwareHeader;

void Protocol_FlushRx(void);
uint16_t Protocol_CRC16(const uint8_t *data, uint32_t length, uint16_t crc);

/* Global packet buffer */
extern uint8_t PacketBuffer[PACKET_SIZE];

/* Bootloader Commands */
#define CMD_UPDATE     'U'
#define CMD_HEADER     'H'
#define CMD_DATA       'D'
#define CMD_END        'E'
#define CMD_JUMP       'J'
#define CMD_GET_VERSION    0x04
/* Responses */
#define ACK            0x79
#define NACK           0x1F

HAL_StatusTypeDef Protocol_ReceiveHeader(void);
HAL_StatusTypeDef Protocol_ReceivePacket(uint16_t length);

void Protocol_SendACK(void);
void Protocol_SendNACK(void);
void Protocol_SendBootloaderReady(void);

#endif
