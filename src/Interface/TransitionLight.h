#ifndef TRANSITION_LIGHT_MODEL
#define TRANSITION_LIGHT_MODEL

#include "./ILightable.h"
#include <ArduinoJson.h>

class TransitionLight : public ILightable
{
public:
    TransitionLight();
    TransitionLight(JsonArray config);
    void start();
    void stop();

private:
    JsonArray _config;
};

#endif