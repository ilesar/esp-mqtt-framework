#include "./LedStripModule.h"

LedStripModule::LedStripModule(int digitalPin, int numberOfLights)
{
    _pin = digitalPin;
    _length = numberOfLights;
    _pixels = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
    _lightFactory = new LightFactory();
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
    if (_light != NULL) {
        _light->stop();
    }

    _light = NULL;
    Serial.println(configuration["configs"].size());
    serializeJson(configuration, Serial);
    _light = _lightFactory->getLight(type, configuration);
    // ILightable *light = _lightFactory->getLight(type, configuration);
    _light->setPixels(&_pixels);

    _light->start();
}