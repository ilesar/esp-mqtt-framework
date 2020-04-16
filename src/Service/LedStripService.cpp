#include "../Interface/LedStripService.h"

LedStripService::LedStripService(int digitalPin, int numberOfLights)
{
    _pin = digitalPin;
    _length = numberOfLights;
    _pixels = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
    _lightFactory = new LightFactory();
}

void LedStripService::connect()
{
    _pixels.begin();
}

void LedStripService::applyPreset(LightType type, bool fadeOut)
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

void LedStripService::applyPreset(LightType type, JsonObject &configuration)
{
    if (_light != NULL) {
        _light->stop();
        _light = NULL;
    }

    _light = _lightFactory->getLight(type, configuration);
    // ILightable *light = _lightFactory->getLight(type, configuration);
    _light->setPixels(&_pixels);

    _light->start();
}