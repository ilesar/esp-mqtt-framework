#include "../Interface/MqttService.h"

MqttService::MqttService(char* host, int port, char* deviceId)
{
    _host = host;
    _port = port;
    _deviceId = deviceId;
    _client = PubSubClient(_wifiClient);
}

void MqttService::setup(void (*callback)(char *charTopic, uint8_t *payload, unsigned int length))
{
    _client.setServer(_host, _port);
    Serial.println("Setting callback");
    _client.setCallback(callback);
}

void MqttService::loop()
{
    connect();
    _client.loop();
}

void MqttService::connect()
{
    if (!_client.connected())
    {
        reconnect();
    }
}

void MqttService::reconnect()
{
    Serial.println("Connecting to MQTT...");
    while (!_client.connected())
    {
        String clientId = "ledstrip-";
        clientId += String(random(0xffff), HEX);

        if (_client.connect(clientId.c_str()))
        {

            _client.subscribe(_deviceId);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(_client.state());

            delay(5000);
        }
    }
    Serial.println("Connected to MQTT");
    _client.publish("configuration", _deviceId);
}