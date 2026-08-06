#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <Arduino.h>

uint32_t CRC32_CalculateBuffer(const uint8_t *data,
                               uint32_t length);

#endif