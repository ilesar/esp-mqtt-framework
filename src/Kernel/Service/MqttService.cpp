#include "../Interface/MqttService.h"

MqttService::MqttService(char *host, int port, IModule* deviceModule)
{
    _host = host;
    _port = port;
    _deviceModule = deviceModule;
    _client = PubSubClient(_wifiClient);

    _configTopic = (char *)malloc(strlen(_deviceModule->getDeviceId()) + strlen("%s/config") + 1);
    _actionTopic = (char *)malloc(strlen(_deviceModule->getDeviceId()) + strlen("%s/action") + 1);

    sprintf(_configTopic, "%s/config", _deviceModule->getDeviceId());
    sprintf(_actionTopic, "%s/action", _deviceModule->getDeviceId());
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

    JsonObject defaultConfiguration = _deviceModule->getDefaultConfiguration();
    String serializedConfiguration;
    serializeJson(_deviceModule->getDefaultConfiguration(), serializedConfiguration);
    Serial.println("SENDING");
    Serial.println(serializedConfiguration.c_str());
    _client.publish("configuration", serializedConfiguration.c_str());
    // _client.publish("configuration", _deviceModule.getDeviceId());
}

void MqttService::onMqttMessage(char *charTopic, uint8_t *payload, unsigned int length)
{
    String topic = (String)charTopic;

    payload[length] = '\0';
    char *message = (char *)payload;

    DynamicJsonDocument doc(4096);
    auto error = deserializeJson(doc, message);

    if (error)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
    }

    JsonObject configuration = doc.as<JsonObject>();

    sprintf(_configTopic, "%s/config", _deviceModule->getDeviceId());
    sprintf(_actionTopic, "%s/action", _deviceModule->getDeviceId());

    
    Serial.println("GOT TOPIC");
    Serial.println(topic);
    Serial.println(_actionTopic);
    Serial.println(_configTopic);


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