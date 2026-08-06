#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <Arduino.h>

/****************************************************
 * Authentication Status
 ****************************************************/
bool Auth_Init();

bool Auth_VerifyDevice();

bool Auth_VerifyToken();

bool Auth_IsAuthenticated();

/****************************************************
 * Device Information
 ****************************************************/
uint32_t Auth_GetDeviceID();
void Auth_SetDeviceID(uint32_t deviceID);

/****************************************************
 * Set Authentication Data
 ****************************************************/
void Auth_SetDeviceID(const String &deviceID);

void Auth_SetToken(const String &token);

#endif