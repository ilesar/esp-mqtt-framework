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

// void LedStripService::applyPreset(Preset preset)
void LedStripService::applyPreset(LightType type)
{
    // Serial.println("Stopping preset");
    // _preset.stop();
    Serial.println("Assigning preset");
    ILightable *light = _lightFactory->getLight(type);
    Serial.println("Setting pixels");
    light->setPixels(&_pixels);

    // ILightable *light = lightFactory->getLight(Solid);
    // Serial.println("Starting preset");
    // Serial.println("Starting preset");
    Serial.println("Starting preset");
    light->start();
}

// void LedStripService::applyPreset(Preset preset)
void LedStripService::applyPreset(LightType type, JsonObject config)
{
    // Serial.println("Stopping preset");
    // _preset.stop();
    Serial.println("Assigning preset");
    ILightable * light = _lightFactory->getLight(type, config);
    Serial.println("Setting pixels");
    light->setPixels(&_pixels);
    
    // ILightable *light = lightFactory->getLight(Solid);
    // Serial.println("Starting preset");
    // Serial.println("Starting preset");
    Serial.println("Starting preset");
    light->start();
}