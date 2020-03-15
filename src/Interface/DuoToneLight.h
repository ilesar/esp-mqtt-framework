#ifndef DUOTONE_LIGHT_MODEL
#define DUOTONE_LIGHT_MODEL

#include "./ILightable.h"
#include <ArduinoJson.h>

class DuoToneLight : public ILightable
{
public:
    DuoToneLight();
    DuoToneLight(JsonObject config);
    void start();
    void stop();
    void parse(char *data, char *array[]);

private:
    JsonObject _config;
};

#endif