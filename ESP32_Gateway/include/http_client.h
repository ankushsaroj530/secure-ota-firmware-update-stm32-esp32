#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <Arduino.h>

/****************************************************
 * HTTP Client
 ****************************************************/

bool HTTP_CheckServer();

bool HTTP_GetVersion();

void HTTP_ReportStatus(const String &stage, const String &detail = "",
                        int progressPercent = -1,
                        bool includeFirmwareInfo = false);

bool HTTP_DownloadFirmware(const String &filename);

String HTTP_PollCommand();




#endif