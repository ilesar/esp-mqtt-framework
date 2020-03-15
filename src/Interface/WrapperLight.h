#ifndef WRAPPER_LIGHT_MODEL
#define WRAPPER_LIGHT_MODEL

#include "./ILightable.h"
#include <ArduinoJson.h>

class WrapperLight : public ILightable
{
public:
    WrapperLight();
    WrapperLight(JsonObject config);
    void start();
    void stop();
    void parse(char *data, char *array[]);

private:
    JsonObject _config;
};

#endif