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

void LedStripService::applyPreset(LightType type, JsonObject configuration)
{
    // Serial.println("service");
    // serializeJson(config, Serial);
    ILightable *light = _lightFactory->getLight(type, configuration);
    light->setPixels(&_pixels);

    light->start();
}