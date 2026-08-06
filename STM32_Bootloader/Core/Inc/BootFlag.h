#ifndef BOOT_FLAG_H
#define BOOT_FLAG_H

#include <stdint.h>

#define BOOT_FLAG_UPDATE_REQUEST   0xA55AU

void     BootFlag_Init(void);
uint16_t BootFlag_Read(void);
uint8_t  BootFlag_IsUpdateRequested(void);
void     BootFlag_SetUpdateRequest(void);
void     BootFlag_Clear(void);

#endif
