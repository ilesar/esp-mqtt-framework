#include "./LedStripModule.h"

LedStripModule::LedStripModule(char *deviceId, int digitalPin, int numberOfLights) : IModule(deviceId)
{
    _pin = digitalPin;
    _length = numberOfLights;
    _pixels = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
    _lightFactory = new LightFactory();

    setDefaultConfiguration();

    _pixels.begin();
}

void LedStripModule::applyPreset(LightType type, bool fadeOut)
{
    if (_light != NULL && fadeOut == true)
    {
        Serial.println("sTOPPING");
        _light->stop();
    }

    _light = NULL;
    Serial.println("CRERATING LIGHT");
    _light = _lightFactory->getLight(type);

    Serial.println("SETTING PIXELS");
    _light->setPixels(&_pixels);
    Serial.println("starting");
    _light->start();
    Serial.println("started");
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
}
