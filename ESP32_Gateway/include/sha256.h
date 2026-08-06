#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void sha256(const void *data,
            uint64_t len,
            void *output);

#ifdef __cplusplus
}
#endif

#endif