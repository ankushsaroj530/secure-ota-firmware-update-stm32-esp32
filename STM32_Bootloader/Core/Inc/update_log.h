#ifndef UPDATE_LOG_H
#define UPDATE_LOG_H

#include <stdint.h>

void UpdateLog_Print(uint32_t oldVersion,
                     uint32_t newVersion,
                     uint32_t deviceID,
                     uint8_t auth,
                     uint8_t erase,
                     uint8_t crc,
                     uint8_t sha,
                     uint8_t status);

#endif
