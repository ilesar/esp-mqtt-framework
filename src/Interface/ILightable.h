#ifndef PRESET_MODEL
#define PRESET_MODEL

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "../Enum/LightType.h"

class ILightable
{
public:
    ILightable();
    virtual void start();
    virtual void stop();
    void setPixels(Adafruit_NeoPixel* pixels);
    Adafruit_NeoPixel _pixels;

protected:
    char* _options;
    
};

#endif