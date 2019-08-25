#ifndef LED_STRIP_SERVICE
#define LED_STRIP_SERVICE

#include <Adafruit_NeoPixel.h>
#include "./SolidLight.h"
#include "./ILightable.h"

class LedStripService
{
public:
    LedStripService(int digitalPin, int numberOfLights);
    void connect();
    void applyPreset(int type);

private:
    Adafruit_NeoPixel _pixels;
    int _pin;
    int _length;
    SolidLight _preset;
};

#endif