#include "Checksum.h"

uint32_t CRC32_CalculateFlash(uint32_t Address, uint32_t Length)
{
    uint32_t crc = 0xFFFFFFFF;

    for (uint32_t i = 0; i < Length; i++)
    {
        uint8_t data = *(volatile uint8_t *)(Address + i);

        crc ^= data;

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }

    return crc ^ 0xFFFFFFFF;
}