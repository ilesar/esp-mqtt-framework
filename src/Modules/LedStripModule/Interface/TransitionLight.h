#ifndef TRANSITION_LIGHT_MODEL
#define TRANSITION_LIGHT_MODEL

#include "./ILightable.h"
#include <ArduinoJson.h>

class TransitionLight : public ILightable
{
public:
    TransitionLight();
    TransitionLight(JsonObject configuration);
    void start();
    void stop();

private:
    JsonObject _configuration;
};

#endif