#include "wifi_manager.h"
#include "config.h"
#include "logger.h"

void WiFi_Init()
{
    Log_Info("Connecting to WiFi...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint32_t start = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        if (millis() - start > 15000)
        {
            Serial.println();
            Log_Error("WiFi Connection Timeout");
            return;
        }
    }

    Serial.println();

    Log_Info("WiFi Connected");
    Log_Info("IP Address : " + WiFi.localIP().toString());
    Log_Info("RSSI : " + String(WiFi.RSSI()) + " dBm");
}

void WiFi_Reconnect()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    Log_Error("WiFi Disconnected");
    Log_Info("Reconnecting...");

    WiFi.disconnect(true);
    delay(500);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint32_t start = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        if (millis() - start > 15000)
        {
            Serial.println();
            Log_Error("WiFi Reconnect Timeout");
            return;
        }
    }

    Serial.println();

    Log_Info("WiFi Reconnected");
    Log_Info("IP Address : " + WiFi.localIP().toString());
}

bool WiFi_IsConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}

String WiFi_GetIP()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return WiFi.localIP().toString();
    }

    return "";
}

int WiFi_GetRSSI()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return WiFi.RSSI();
    }

    return 0;
}