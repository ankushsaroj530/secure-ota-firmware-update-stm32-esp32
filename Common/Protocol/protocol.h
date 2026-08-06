#ifndef OTA_PROTOCOL_H
#define OTA_PROTOCOL_H

/*-------------------------------------------------
            UART Commands
-------------------------------------------------*/

#define CMD_GET_VERSION          0x04
#define CMD_ENTER_BOOTLOADER     0x55

#define CMD_UPDATE               'U'
#define CMD_DATA                 'D'
#define CMD_END                  'E'
#define CMD_EXIT                 0x05

/*-------------------------------------------------
            Responses
-------------------------------------------------*/

#define RESP_ACK                 "ACK"
#define RESP_NACK                "NACK"
#define RESP_VERSION             "VERSION"

/*-------------------------------------------------
            Packet Size
-------------------------------------------------*/

#define OTA_PACKET_SIZE          256

#endif