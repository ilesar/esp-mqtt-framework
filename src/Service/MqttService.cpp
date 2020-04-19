#include "../Interface/MqttService.h"


MqttService::MqttService(char *host, int port, char *deviceId)
{
    _host = host;
    _port = port;
    _deviceId = deviceId;
    _client = PubSubClient(_wifiClient);
}

void MqttService::setup(void (*callback)(String message, JsonObject configuration))
{
    _callback = callback;
    _client.setServer(_host, _port);
    _client.setCallback([this](char *topic, byte *payload, unsigned int length) { this->onMqttMessage(topic, payload, length); });
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

void MqttService::install()
{
    // todo: register device to backend
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

void MqttService::onMqttMessage(char *charTopic, uint8_t *payload, unsigned int length)
{
    String topic = (String)charTopic;

    payload[length] = '\0';
    char *message = (char *)payload;

    Serial.println(message);
    DynamicJsonDocument doc(4096);
    auto error = deserializeJson(doc, message);

    if (error)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
    }

    JsonObject configuration = doc.as<JsonObject>();

    _callback(topic, configuration);
}