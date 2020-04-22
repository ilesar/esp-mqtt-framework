#ifndef LED_STRIP_MODULE
#define LED_STRIP_MODULE

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "./Interface/SolidLight.h"
#include "./Interface/ILightable.h"
#include "./Helper/LightFactory.cpp"
#include "../../Interface/IModule.h"

class LedStripModule : public IModule
{
public:
    LedStripModule(char *deviceId, int digitalPin, int numberOfLights);
    LedStripModule(const LedStripModule &) = delete;
    void connect();
    void applyPreset(LightType type, bool fadeOut = true);
    void applyPreset(LightType type, JsonObject &configuration);
    JsonObject getDefaultConfiguration();

private:
    void setDefaultConfiguration();
    DynamicJsonDocument doc = DynamicJsonDocument(4096);
    JsonObject _defaultConfiguration;
    Adafruit_NeoPixel _pixels;
    int _pin;
    int _length;
    LightFactory *_lightFactory;
    ILightable *_light = NULL;
};

#endif