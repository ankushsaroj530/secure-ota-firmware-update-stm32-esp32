#include "update_log.h"
#include <stdio.h>

void UpdateLog_Print(uint32_t oldVersion,
                     uint32_t newVersion,
                     uint32_t deviceID,
                     uint8_t auth,
                     uint8_t erase,
                     uint8_t crc,
                     uint8_t sha,
                     uint8_t status)
{
    printf("\r\n");
    printf("========================================\r\n");
    printf("             UPDATE LOG\r\n");
    printf("========================================\r\n");

    printf("Device ID      : %lu\r\n", deviceID);
    printf("Old Version    : %lu\r\n", oldVersion);
    printf("New Version    : %lu\r\n", newVersion);

    printf("Authentication : %s\r\n", auth ? "PASS" : "FAIL");
    printf("Flash Erase    : %s\r\n", erase ? "PASS" : "FAIL");
    printf("CRC32          : %s\r\n", crc ? "PASS" : "FAIL");
    printf("SHA-256        : %s\r\n", sha ? "PASS" : "FAIL");

    printf("Status         : %s\r\n",
           status ? "SUCCESS" : "FAILED");

    printf("========================================\r\n");
}
