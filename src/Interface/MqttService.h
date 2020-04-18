#ifndef MQTT_SERVICE
#define MQTT_SERVICE

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define MQTT_SERVICE_CALLBACK_SIGNATURE void (*callback)(String topic, JsonObject configuration)

class MqttService
{
public:
    MqttService(char *host, int port, char *deviceId);
    void setup(void (*callback)(char *charTopic, uint8_t *payload, unsigned int length));
    void connect();
    void loop();

private:
    void reconnect();
    WiFiClient _wifiClient;
    PubSubClient _client;

    char *_host;
    int _port;
    char *_deviceId;
};

#endif