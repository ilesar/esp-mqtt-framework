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

void LedStripService::applyPreset(LightType type)
{
    ILightable *light = _lightFactory->getLight(type);
    light->setPixels(&_pixels);

    light->start();
}

void LedStripService::applyPreset(LightType type, JsonObject config)
{
    ILightable * light = _lightFactory->getLight(type, config);
    light->setPixels(&_pixels);
    
    light->start();
}