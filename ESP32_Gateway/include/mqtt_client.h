#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Arduino.h>

/****************************************************
 * MQTT Functions
 ****************************************************/
void MQTT_Init();

void MQTT_Connect();

bool MQTT_IsConnected();

void MQTT_Loop();

bool MQTT_Publish(const String &topic,
                  const String &message);

bool MQTT_Subscribe(const String &topic);

#endif