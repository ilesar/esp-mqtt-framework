#include "../Interface/LedStripService.h"

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
    Serial.println("Assigning preset");
    _preset = SolidLight(255, 0, 0);
    Serial.println("Setting pixels");
    _preset.setPixels(&_pixels);
    Serial.println("Starting preset");
    _preset.start();
}