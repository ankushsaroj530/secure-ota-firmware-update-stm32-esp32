#include "mqtt_client.h"
#include "config.h"
#include "logger.h"

#include <WiFi.h>
#include <PubSubClient.h>

/****************************************************
 * Global Objects
 ****************************************************/
WiFiClient espClient;
PubSubClient mqttClient(espClient);

/****************************************************
 * MQTT Callback
 ****************************************************/
void MQTT_Callback(char *topic, byte *payload, unsigned int length)
{
    String message = "";

    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Log_Info("MQTT Topic : " + String(topic));
    Log_Info("MQTT Message : " + message);
}

/****************************************************
 * Initialize MQTT
 ****************************************************/
void MQTT_Init()
{
    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);

    mqttClient.setCallback(MQTT_Callback);

    Log_Info("MQTT Initialized");
}

/****************************************************
 * Connect MQTT Broker
 ****************************************************/
void MQTT_Connect()
{
    while (!mqttClient.connected())
    {
        Log_Info("Connecting MQTT...");

        if (mqttClient.connect(MQTT_CLIENT_ID))
        {
            Log_Info("MQTT Connected");

            mqttClient.subscribe(MQTT_TOPIC_UPDATE);

            Log_Info("Subscribed : " + String(MQTT_TOPIC_UPDATE));
        }
        else
        {
            Log_Error("MQTT Connection Failed");

            delay(3000);
        }
    }
}

/****************************************************
 * MQTT Connected ?
 ****************************************************/
bool MQTT_IsConnected()
{
    return mqttClient.connected();
}

/****************************************************
 * MQTT Loop
 ****************************************************/
void MQTT_Loop()
{
    if (!mqttClient.connected())
    {
        MQTT_Connect();
    }

    mqttClient.loop();
}

/****************************************************
 * Publish
 ****************************************************/
bool MQTT_Publish(const String &topic,
                  const String &message)
{
    if (!mqttClient.connected())
    {
        MQTT_Connect();
    }

    bool status = mqttClient.publish(
        topic.c_str(),
        message.c_str());

    if (status)
    {
        Log_Info("Published -> " + topic);
    }
    else
    {
        Log_Error("Publish Failed");
    }

    return status;
}

/****************************************************
 * Subscribe
 ****************************************************/
bool MQTT_Subscribe(const String &topic)
{
    if (!mqttClient.connected())
    {
        MQTT_Connect();
    }

    bool status = mqttClient.subscribe(topic.c_str());

    if (status)
    {
        Log_Info("Subscribed -> " + topic);
    }
    else
    {
        Log_Error("Subscribe Failed");
    }

    return status;
}