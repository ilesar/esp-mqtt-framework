#ifndef MQTT_SERVICE
#define MQTT_SERVICE

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "../Interface/IKernelService.h"

#define CONFIGURATION_CALLBACK void (*configurationCallback)(JsonObject configuration)
#define ACTION_CALLBACK void (*actionCallback)(JsonObject configuration)

class MqttService : public IKernelService
{
public:
    MqttService(char *host, int port, char *deviceId);    
    void setup(CONFIGURATION_CALLBACK, ACTION_CALLBACK);
    void loop();

    char *configTopic();
    char *actionTopic();

private:
    void connect();
    void reconnect();
    void onMqttMessage(char *charTopic, uint8_t *payload, unsigned int length);
    
    WiFiClient _wifiClient;
    PubSubClient _client;

    char *_host;
    int _port;
    char *_deviceId;
    char *_configTopic;
    char *_actionTopic;
    void (*_configurationCallback)(JsonObject configuration);
    void (*_actionCallback)(JsonObject configuration);
};

#endif