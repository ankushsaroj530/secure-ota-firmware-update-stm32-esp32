#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

/*====================================================
                Logger Initialization
====================================================*/
void Logger_Init();

/*====================================================
                Log Functions
====================================================*/
void Log_Info(const String &message);

void Log_Warning(const String &message);

void Log_Error(const String &message);

#endif