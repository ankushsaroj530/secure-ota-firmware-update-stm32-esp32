#include "logger.h"

void Logger_Init()
{
    Serial.println();
    Serial.println("====================================");
    Serial.println(" Secure OTA Firmware System");
    Serial.println(" ESP32 Gateway Started");
    Serial.println("====================================");
}

void Log_Info(const String &message)
{
    Serial.print("[INFO] ");
    Serial.println(message);
}

void Log_Warning(const String &message)
{
    Serial.print("[WARNING] ");
    Serial.println(message);
}

void Log_Error(const String &message)
{
    Serial.print("[ERROR] ");
    Serial.println(message);
}