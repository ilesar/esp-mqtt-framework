#ifndef MQTT_SERVICE
#define MQTT_SERVICE

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MqttService
{
public:
    MqttService(char *host, int port, char *deviceId);
    void setup(void (*callback)(String message, JsonObject configuration));
    void connect();
    void loop();

private:
    void reconnect();
    void onMqttMessage(char *charTopic, uint8_t *payload, unsigned int length);
    
    WiFiClient _wifiClient;
    PubSubClient _client;

    char *_host;
    int _port;
    char *_deviceId;
    void (*_callback)(String message, JsonObject configuration);
};

#endif