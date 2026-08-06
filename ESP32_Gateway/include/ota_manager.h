#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <Arduino.h>
#include "ota_state.h"

/* OTA State */
extern OTA_State CurrentState;

/* Version Management */
bool OTA_CheckVersion();
uint32_t OTA_GetInstalledVersion();
uint32_t OTA_GetServerVersion();

/* Bootloader Control */
bool OTA_RequestBootloader();
bool OTA_WaitBootloader();

/* Firmware Update */
bool OTA_SendHeader();
bool OTA_SendFirmware();
bool OTA_SendEnd();

/* Complete OTA Process */
bool OTA_StartUpdate();
void OTA_SetServerVersion(uint32_t version);
bool OTA_SendExit();

#endif