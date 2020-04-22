#include "./LedStripModule.h"

LedStripModule::LedStripModule(char *deviceId, int digitalPin, int numberOfLights) : IModule(deviceId)
{
    _pin = digitalPin;
    _length = numberOfLights;
    _pixels = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
    _lightFactory = new LightFactory();

    setDefaultConfiguration();
    Serial.println("DONE");
    serializeJson(_defaultConfiguration, Serial);
    Serial.println("");
    serializeJson(getDefaultConfiguration(), Serial);
    Serial.println("");
}

void LedStripModule::connect()
{
    _pixels.begin();
}

void LedStripModule::applyPreset(LightType type, bool fadeOut)
{
    if (_light != NULL && fadeOut == true)
    {
        _light->stop();
    }

    _light = NULL;
    _light = _lightFactory->getLight(type);

    _light->setPixels(&_pixels);

    _light->start();
}

void LedStripModule::applyPreset(LightType type, JsonObject &configuration)
{
    if (_light != NULL)
    {
        _light->stop();
    }

    _light = NULL;

    _light = _lightFactory->getLight(type, configuration);
    _light->setPixels(&_pixels);

    _light->start();
}

void LedStripModule::setDefaultConfiguration()
{
    _defaultConfiguration = doc.to<JsonObject>();

    _defaultConfiguration["deviceId"] = _deviceId;

    JsonArray configurationArray = _defaultConfiguration.createNestedArray("configs");

    for (int i = 0; i < _length; i++)
    {
        JsonObject configurationObject = configurationArray.createNestedObject();
        configurationObject["r"] = 255;
        configurationObject["g"] = 255;
        configurationObject["b"] = 255;
        configurationObject["type"] = "color";
    }

    // Serial.println("DEFAULT");
    // serializeJson(_defaultConfiguration, Serial);
    // Serial.println("");
}

JsonObject LedStripModule::getDefaultConfiguration()
{
    Serial.println("GETTING CONFIGURATION");
    return _defaultConfiguration;
}