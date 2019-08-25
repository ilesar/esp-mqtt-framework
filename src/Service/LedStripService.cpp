#include "../Interface/LedStripService.h"
#include "../Helper/LightFactory.cpp"

LedStripService::LedStripService(int digitalPin, int numberOfLights)
{
    _pin = digitalPin;
    _length = numberOfLights;
    _pixels = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
}

void LedStripService::connect()
{
    _pixels.begin();
}

// void LedStripService::applyPreset(Preset preset)
void LedStripService::applyPreset(int type)
{
    // Serial.println("Stopping preset");
    // _preset.stop();
    LightFactory * lightFactory = new LightFactory();
    Serial.println("Assigning preset");
    ILightable * light = lightFactory->getLight(Solid);
    Serial.println("Setting pixels");
    light->setPixels(&_pixels);
    // Serial.println("Starting preset");
    // Serial.println("Starting preset");
    Serial.println("Starting preset");
    light->start();
}