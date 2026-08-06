#include "http_client.h"
#include "config.h"
#include "logger.h"
#include "firmware_manager.h"
#include "ota_manager.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <esp_task_wdt.h>   // <-- here
/* Applied to every HTTPClient call in this file so a slow/cold-starting
 * server (e.g. Render free tier waking from sleep) can never block long
 * enough to starve the ESP32 task watchdog or outlast the STM32's UART
 * idle timeout. */
#define HTTP_CONNECT_TIMEOUT_MS 20000
#define HTTP_RESPONSE_TIMEOUT_MS 45000

/****************************************************
 * Check Server Connection
 ****************************************************/
bool HTTP_CheckServer()
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    String url = String(SERVER_URL) + "/";

    Log_Info("Connecting to Server: " + String(SERVER_URL));

    http.begin(client, url);
    http.setConnectTimeout(HTTP_CONNECT_TIMEOUT_MS);
    http.setTimeout(HTTP_RESPONSE_TIMEOUT_MS);

    int code = http.GET();

    http.end();

    if (code > 0)
    {
        Log_Info("Server Reachable (HTTP " + String(code) + ")");
        return true;
    }
    else
    {
        Log_Error("Server Connection Failed (code " + String(code) + ")");
        return false;
    }
}

/****************************************************
 * Get Latest Firmware Information
 ****************************************************/
bool HTTP_GetVersion()
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    String url = String(SERVER_URL) + String(VERSION_API);

    Log_Info("Checking Firmware Version...");

    http.begin(client, url);
    http.setConnectTimeout(HTTP_CONNECT_TIMEOUT_MS);
    http.setTimeout(HTTP_RESPONSE_TIMEOUT_MS);

    int code = http.GET();

    if (code != HTTP_CODE_OK)
    {
        Log_Error("Failed to Read Version (code " + String(code) + ")");
        http.end();
        return false;
    }

    String payload = http.getString();

    http.end();

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error)
    {
        Log_Error("JSON Parse Failed");
        return false;
    }

    uint32_t version = doc["version"];
    String filename = doc["filename"];
    uint32_t size = doc["size"];

    /* Save latest server version */
    OTA_SetServerVersion(version);

    /* Save filename for later download */
    FirmwareFileName = filename;

    Log_Info("Latest Version : " + String(version));
    Log_Info("Firmware File  : " + filename);
    Log_Info("Firmware Size  : " + String(size) + " Bytes");

    return true;
}

/****************************************************
 * Download Firmware
 ****************************************************/
bool HTTP_DownloadFirmware(const String &filename)
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    String url = String(SERVER_URL) + String(DOWNLOAD_API) + "/" + filename;

    Log_Info("Downloading Firmware...");
    Log_Info(url);

    http.begin(client, url);
    http.setConnectTimeout(HTTP_CONNECT_TIMEOUT_MS);
    http.setTimeout(HTTP_RESPONSE_TIMEOUT_MS);

    int code = http.GET();

    if (code != HTTP_CODE_OK)
    {
        Log_Error("Download Failed (code " + String(code) + ")");
        http.end();
        return false;
    }

    WiFiClient *stream = http.getStreamPtr();

    int total = http.getSize();

    if (total <= 0)
    {
        Log_Error("Invalid Firmware Size");
        http.end();
        return false;
    }

    /* Free previous firmware */
    Firmware_Clear();

    /* Allocate memory */
    FirmwareBuffer = (uint8_t *)malloc(total);

    if (FirmwareBuffer == nullptr)
    {
        Log_Error("Memory Allocation Failed");
        http.end();
        return false;
    }

    FirmwareSize = total;

    int received = 0;

    while (http.connected() && (received < total))
    {
        /* Feed the watchdog during a potentially long, chunked download
         * so a slow connection can't trip the task watchdog mid-transfer. */
        esp_task_wdt_reset();

        size_t available = stream->available();

        if (available)
        {
            int len = stream->readBytes(
                FirmwareBuffer + received,
                min((size_t)(total - received), available));

            received += len;

            int percent = (received * 100) / total;

            Log_Info("Download : " + String(percent) + "%");
        }

        delay(1);
    }

    http.end();

    if (received != total)
    {
        Log_Error("Firmware Download Incomplete");

        Firmware_Clear();

        return false;
    }

    Log_Info("Firmware Download Completed");
    Log_Info("Firmware Size : " + String(FirmwareSize) + " Bytes");

    return true;
}


void HTTP_ReportStatus(const String &stage, const String &detail,
                        int progressPercent, bool includeFirmwareInfo)
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    String url = String(SERVER_URL) + "/api/status";

    http.begin(client, url);
    http.setConnectTimeout(HTTP_CONNECT_TIMEOUT_MS);
    http.setTimeout(HTTP_RESPONSE_TIMEOUT_MS);
    http.addHeader("Content-Type", "application/json");

    /* node_id is the dashboard routing key and MUST be sent on every
     * call, not just when firmware info is attached. It is different
     * from FirmwareHeader.deviceID (the numeric auth ID) below. */
    String body = "{";
    body += "\"node_id\":\"" + String(NODE_ID) + "\",";
    body += "\"stage\":\"" + stage + "\",";
    body += "\"detail\":\"" + detail + "\",";
    body += "\"installed_version\":" + String(OTA_GetInstalledVersion()) + ",";
    body += "\"server_version\":" + String(OTA_GetServerVersion());

    if (progressPercent >= 0)
    {
        body += ",\"progress_percent\":" + String(progressPercent);
    }

    if (includeFirmwareInfo)
    {
        body += ",\"firmware_file\":\"" + FirmwareFileName + "\"";
        body += ",\"firmware_size\":" + String(FirmwareHeader.firmwareSize);
        body += ",\"header_size\":" + String(sizeof(FirmwareHeader));
        body += ",\"device_id\":" + String(FirmwareHeader.deviceID);

        char crcHex[12];
        sprintf(crcHex, "0x%08lX", (unsigned long)FirmwareHeader.firmwareCRC);
        body += ",\"crc32\":\"" + String(crcHex) + "\"";

        String shaHex = "";
        for (int i = 0; i < 32; i++)
        {
            char b[3];
            sprintf(b, "%02X", FirmwareHeader.sha256[i]);
            shaHex += b;
        }
        body += ",\"sha256\":\"" + shaHex + "\"";

        body += ",\"auth_token\":\"" + String(AUTH_TOKEN) + "\"";
    }

    body += "}";

    int code = http.POST(body);
    http.end();

    if (code <= 0)
    {
        Log_Warning("Status report failed");
    }
}

String HTTP_PollCommand()
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    String url = String(SERVER_URL) + "/api/command";

    http.begin(client, url);
    http.setConnectTimeout(HTTP_CONNECT_TIMEOUT_MS);
    http.setTimeout(HTTP_RESPONSE_TIMEOUT_MS);

    int code = http.GET();

    String result = "";

    if (code == HTTP_CODE_OK)
    {
        String payload = http.getString();

        JsonDocument doc;
        if (deserializeJson(doc, payload) == DeserializationError::Ok)
        {
            if (!doc["command"].isNull())
            {
                result = doc["command"].as<String>();
            }
        }
    }

    http.end();
    return result;
}