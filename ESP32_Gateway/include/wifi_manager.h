#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

/* Initialize Wi-Fi */
void WiFi_Init();

/* Reconnect if disconnected */
void WiFi_Reconnect();

/* Check connection status */
bool WiFi_IsConnected();

/* Get local IP address */
String WiFi_GetIP();

/* Get Wi-Fi signal strength (RSSI) */
int WiFi_GetRSSI();

#endif