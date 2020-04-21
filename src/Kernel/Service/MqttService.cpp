#include "../Interface/MqttService.h"

MqttService::MqttService(char *host, int port, char *deviceId)
{
    _host = host;
    _port = port;
    _deviceId = deviceId;
    _client = PubSubClient(_wifiClient);

    Serial.println("");
    Serial.println("tpc");

    _configTopic = (char *)malloc(strlen(_deviceId) + strlen("%s/config") + 1);
    _actionTopic = (char *)malloc(strlen(_deviceId) + strlen("%s/action") + 1);
    Serial.println(_configTopic);
    Serial.println(_actionTopic);

    sprintf(_configTopic, "%s/config", _deviceId);
    Serial.println(_configTopic);
    Serial.println(_actionTopic);
    sprintf(_actionTopic, "%s/action", _deviceId);

    Serial.println(_configTopic);
    Serial.println(_actionTopic);
}

void MqttService::setup(CONFIGURATION_CALLBACK, ACTION_CALLBACK)
{
    _configurationCallback = configurationCallback;
    _actionCallback = actionCallback;

    _client.setServer(_host, _port);

#ifndef __INTELLISENSE__
    _client.setCallback([this](char *topic, byte *payload, unsigned int length) { this->onMqttMessage(topic, payload, length); });
#endif

    connect();
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
            _client.subscribe(_configTopic);
            _client.subscribe(_actionTopic);
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

    Serial.println("GOT MESSAGE");
    Serial.println(message);
    DynamicJsonDocument doc(4096);
    auto error = deserializeJson(doc, message);

    if (error)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
    }

    JsonObject configuration = doc.as<JsonObject>();

    if (topic == _actionTopic)
    {
        Serial.println(_actionTopic);
        _actionCallback(configuration);
        Serial.println("END");
    }
    else if (topic == _configTopic)
    {
        Serial.println(_configTopic);
        _configurationCallback(configuration);
        Serial.println("END");
    }
}

char *MqttService::configTopic()
{
    return _configTopic;
}

char *MqttService::actionTopic()
{
    return _actionTopic;
}