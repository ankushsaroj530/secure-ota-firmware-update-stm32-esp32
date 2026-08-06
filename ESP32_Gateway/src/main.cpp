#include <Arduino.h>
#include <esp_task_wdt.h>

#include "logger.h"
#include "config.h"
#include "wifi_manager.h"
#include "uart_manager.h"
#include "http_client.h"
#include "ota_manager.h"

bool otaCompleted = false;


unsigned long lastAttemptTime = 0;
const unsigned long RETRY_INTERVAL_MS = 60000;   // retry every 60s on failure

/* Widened from 30 -> 120s. A cold Render instance can take 30-60s to wake
 * on the first request; the old 30s ceiling meant a single slow HTTP call
 * during checking_server/checking_stm32 could trip the watchdog and force
 * an ESP32 reboot mid-cycle, which then re-triggered STM32_HardReset() and
 * looked like an uncommanded repeat update. */
const int WDT_TIMEOUT_SEC = 120;

/*====================================================
                Run One Full OTA Check Cycle
====================================================*/
bool RunOtaCycle()
{
    HTTP_ReportStatus("checking_stm32", "");

    bool communicationOK = false;
    for (int i = 0; i < 10; i++)
    {
        esp_task_wdt_reset();

        if (OTA_CheckVersion())
        {
            communicationOK = true;
            break;
        }
        delay(1000);
        esp_task_wdt_reset();
    }

    if (!communicationOK)
    {
        HTTP_ReportStatus("stm32_unreachable", "No response after 10 tries");
        return false;
    }

    HTTP_ReportStatus("checking_server", "");

    /* Reset immediately before each blocking network call so a slow/
     * cold-starting server can't silently eat into the watchdog budget. */
    esp_task_wdt_reset();
    if (!HTTP_CheckServer())
    {
        HTTP_ReportStatus("server_offline", "");
        return false;
    }

    esp_task_wdt_reset();
    if (!HTTP_GetVersion())
    {
        HTTP_ReportStatus("version_check_failed", "");
        return false;
    }

    uint32_t installedVersion = OTA_GetInstalledVersion();
    uint32_t serverVersion    = OTA_GetServerVersion();

    if (installedVersion >= serverVersion)
    {
        HTTP_ReportStatus("up_to_date", "");
        OTA_SendExit();
        return true;
    }

    HTTP_ReportStatus("downloading", "", 0);

    esp_task_wdt_reset();
    if (!OTA_StartUpdate())   // add HTTP_ReportStatus("sending_data", "", percent) inside OTA_SendFirmware's loop too
    {
        HTTP_ReportStatus("ota_failed", "Update sequence failed");
        return false;
    }

    HTTP_ReportStatus("ota_success", "Updated to v" + String(serverVersion), 100, true);

    return true;
}


void setup()
{
    Serial.begin(115200);
    delay(1000);

    Logger_Init();
    UART_Init();

    /* Watchdog: recovers automatically from any unexpected hang */
    esp_task_wdt_init(WDT_TIMEOUT_SEC, true);
    esp_task_wdt_add(NULL);

    WiFi_Init();

    Log_Info("Initialization completed");

    /* Allow STM32 application to boot before probing it */
    delay(3000);

    otaCompleted = RunOtaCycle();

    lastAttemptTime = millis();
}

unsigned long lastCommandPoll = 0;
const unsigned long COMMAND_POLL_INTERVAL_MS = 5000;   // check every 5s

void loop()
{
    esp_task_wdt_reset();

    /* Poll for remote commands from the dashboard */
    if (millis() - lastCommandPoll > COMMAND_POLL_INTERVAL_MS)
    {
        lastCommandPoll = millis();

        String cmd = HTTP_PollCommand();

        if (cmd == "check_now")
        {
            Log_Info("Remote command received: check_now");
            otaCompleted = RunOtaCycle();
            lastAttemptTime = millis();
        }
    }

    if (otaCompleted)
    {
        delay(2000);
        return;
    }

    if (millis() - lastAttemptTime > RETRY_INTERVAL_MS)
    {
        Log_Info("Retrying OTA cycle...");

        if (!WiFi_IsConnected())
        {
            WiFi_Reconnect();
        }

        otaCompleted = RunOtaCycle();
        lastAttemptTime = millis();
    }

    delay(1000);
}