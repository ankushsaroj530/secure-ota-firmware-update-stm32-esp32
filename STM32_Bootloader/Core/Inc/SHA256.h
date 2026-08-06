#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>

#define SHA256_HASH_SIZE 32


void sha256(const void *data,
            uint64_t len,
            void *output);


void SHA256_CalculateFlash(uint32_t flashAddress,
                           uint32_t length,
                           uint8_t hash[SHA256_HASH_SIZE]);


#endif /* SHA256_H */
