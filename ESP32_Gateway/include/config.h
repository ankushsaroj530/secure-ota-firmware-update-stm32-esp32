#ifndef CONFIG_H
#define CONFIG_H

/*====================================================
                    Wi-Fi Configuration
====================================================*/
#define WIFI_SSID          "Ankush"
#define WIFI_PASSWORD      "123456789"

/*====================================================
                  Server Configuration
====================================================*/
// config.h
#define SERVER_URL "https://ota-server-gqmq.onrender.com"

/*====================================================
                  Server Configuration
====================================================*/


// remove these two lines if still present:
// #define SERVER_IP   "10.58.7.162"
// #define SERVER_PORT 5000

// confirm these still exist with a leading "/"
#define VERSION_API  "/api/version"
#define DOWNLOAD_API "/api/download"

/*====================================================
                 Device Information
====================================================*/
#define DEVICE_NAME    "STM32_NODE_01"
#define DEVICE_ID          1
#define AUTH_TOKEN         "STM32_OTA_2026!"
#define NODE_ID            "STM32_NODE_01"

/*====================================================
                 UART Configuration
====================================================*/
#define UART_TX_PIN        17          // ESP32 TX2 -> STM32 RX (PA10)
#define UART_RX_PIN        16          // ESP32 RX2 <- STM32 TX (PA9)
#define UART_BAUDRATE      115200

/*====================================================
                  OTA Commands
====================================================*/
#define CMD_GET_VERSION        0x04
#define CMD_ENTER_BOOTLOADER   0x55

/*====================================================
               UART Timeouts (ms)
====================================================*/
#define VERSION_TIMEOUT        3000
#define ACK_TIMEOUT            3000
#define BOOT_TIMEOUT           5000

/*====================================================
               Firmware Information
====================================================*/
#define CURRENT_VERSION        1

/*====================================================
                     Debug
====================================================*/
#define DEBUG_ENABLE           1

/*====================================================
                MQTT Configuration
====================================================*/
#define MQTT_BROKER        "10.87.230.207"
#define MQTT_PORT          1883

#define MQTT_CLIENT_ID     "ESP32_GATEWAY"

#define MQTT_TOPIC_UPDATE  "stm32/update"
#define MQTT_TOPIC_STATUS  "stm32/status"
#define MQTT_TOPIC_LOG     "stm32/log"

#endif