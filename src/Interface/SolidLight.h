#ifndef SOLID_LIGHT_MODEL
#define SOLID_LIGHT_MODEL

#include "./ILightable.h"
#include <ArduinoJson.h>

class SolidLight : public ILightable
{
public:
    SolidLight();
    SolidLight(int red, int green, int blue);
    void start();
    void stop();
    void parse(char *data, char *array[]);

private:
    int _r;
    int _g;
    int _b;
};

#endif