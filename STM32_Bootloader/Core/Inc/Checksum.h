#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h>

uint32_t CRC32_CalculateFlash(uint32_t Address,
                              uint32_t Length);

#endif /* CHECKSUM_H */