#ifndef BOOT_ANIMATION_LIGHT_MODEL
#define BOOT_ANIMATION_LIGHT_MODEL

#include "./ILightable.h"
#include <ArduinoJson.h>

class BootAnimationLight : public ILightable
{
public:
    BootAnimationLight();
    BootAnimationLight(JsonObject config);
    void start();
    void stop();
    void parse(char *data, char *array[]);

private:
    JsonObject _config;
};

#endif