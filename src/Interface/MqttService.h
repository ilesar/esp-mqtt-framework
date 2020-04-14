#ifndef MQTT_SERVICE
#define MQTT_SERVICE

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MqttService
{
public:
    MqttService(char *host, int port);
    void setup(MQTT_CALLBACK_SIGNATURE);
    void loop();
    

private:
    void reconnect();
    WiFiClient _wifiClient;
    PubSubClient _client;

    char *_host;
    int _port;
};

#endif