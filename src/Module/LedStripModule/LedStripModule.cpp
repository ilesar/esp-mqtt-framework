#include "./LedStripModule.h"

LedStripModule::LedStripModule(char *deviceId, int digitalPin, int numberOfLights) : IModule(deviceId)
{
    _pin = digitalPin;
    _length = numberOfLights;
    _pixels = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
    _lightFactory = new LightFactory();

    setDefaultConfiguration();
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
    Serial.println("APPLYing PRESET");
    if (_light != NULL)
    {
        _light->stop();
    }

    _light = NULL;
    Serial.println("LITE");
    _light = _lightFactory->getLight(type, configuration);
    _light->setPixels(&_pixels);

    Serial.println("STARTING");
    _light->start();
    Serial.println("STARTED");
}

void LedStripModule::setDefaultConfiguration()
{
    DynamicJsonDocument doc(4096);
    JsonObject root = doc.to<JsonObject>();

    JsonArray configurationArray = root.createNestedArray("configs");

    for (int i = 0; i < _length; i++)
    {
        JsonObject configurationObject = configurationArray.createNestedObject();
        configurationObject["r"] = 255;
        configurationObject["g"] = 255;
        configurationObject["b"] = 255;
    }

    Serial.println("def");
    serializeJson(root, Serial);

    defaultConfiguration = root;
}