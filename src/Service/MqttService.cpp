#include "../Interface/MqttService.h"

MqttService::MqttService(char* host, int port)
{
    _host = host;
    _port = port;
    _client = PubSubClient(_wifiClient);
}

void MqttService::setup(MQTT_CALLBACK_SIGNATURE)
{
    _client.setServer(_host, _port);
    _client.setCallback(callback);
}

void MqttService::loop()
{
    if (!_client.connected())
    {
        reconnect();
    }
    _client.loop();
}

void MqttService::reconnect()
{
    while (!_client.connected())
    {
        String clientId = "ledstrip-";
        clientId += String(random(0xffff), HEX);

        if (_client.connect(clientId.c_str()))
        {

            _client.subscribe("home/tv/light/#");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(_client.state());

            delay(5000);
        }
    }
}
