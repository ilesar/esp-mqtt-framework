#ifndef LED_STRIP_SERVICE
#define LED_STRIP_SERVICE

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "./SolidLight.h"
#include "./ILightable.h"
#include "../Helper/LightFactory.cpp"

class LedStripService
{
public:
    LedStripService(int digitalPin, int numberOfLights);
    void connect();
    void applyPreset(LightType type);
    void applyPreset(LightType type, JsonObject configuration);

private:
    Adafruit_NeoPixel _pixels;
    int _pin;
    int _length;
    LightFactory *_lightFactory;
    ILightable *_light;
};

#endif