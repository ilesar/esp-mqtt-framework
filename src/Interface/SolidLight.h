#ifndef SOLID_LIGHT_MODEL
#define SOLID_LIGHT_MODEL

#include "./ILightable.h"
#include <ArduinoJson.h>

class SolidLight : public ILightable
{
public:
    SolidLight();
    SolidLight(int red, int green, int blue);
    SolidLight(JsonObject &configuration);
    void start();
    void stop();

private:
    JsonObject _configuration;

    int dimChannel(int color);
};

#endif