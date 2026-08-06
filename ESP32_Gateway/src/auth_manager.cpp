#include "auth_manager.h"
#include "config.h"
#include "logger.h"

/****************************************************
 * Private Variables
 ****************************************************/
static uint32_t DeviceID = DEVICE_ID;
static String AuthToken = String(AUTH_TOKEN);

static bool Authenticated = false;

/****************************************************
 * Initialize Authentication
 ****************************************************/
bool Auth_Init()
{
    DeviceID = DEVICE_ID;
    AuthToken = String(AUTH_TOKEN);

    Authenticated = false;

    Log_Info("Authentication Manager Initialized");

    return true;
}

/****************************************************
 * Verify Device ID
 ****************************************************/
bool Auth_VerifyDevice()
{
    if (DeviceID == DEVICE_ID)
    {
        Log_Info("Device ID Verified");
        return true;
    }

    Log_Error("Invalid Device ID");
    return false;
}

/****************************************************
 * Verify Authentication Token
 ****************************************************/
bool Auth_VerifyToken()
{
    if (AuthToken.equals(String(AUTH_TOKEN)))
    {
        Log_Info("Authentication Token Verified");

        Authenticated = true;
        return true;
    }

    Log_Error("Authentication Token Invalid");

    Authenticated = false;
    return false;
}

/****************************************************
 * Check Authentication Status
 ****************************************************/
bool Auth_IsAuthenticated()
{
    return Authenticated;
}

/****************************************************
 * Get Device ID
 ****************************************************/
uint32_t Auth_GetDeviceID()
{
    return DeviceID;
}

/****************************************************
 * Get Authentication Token
 ****************************************************/
String Auth_GetToken()
{
    return AuthToken;
}

/****************************************************
 * Set Device ID
 ****************************************************/
void Auth_SetDeviceID(uint32_t deviceID)
{
    DeviceID = deviceID;
}

/****************************************************
 * Set Authentication Token
 ****************************************************/
void Auth_SetToken(const String &token)
{
    AuthToken = token;
}