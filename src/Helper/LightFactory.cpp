#include <ArduinoJson.h>
#include "../Enum/LightType.h"
#include "../Interface/ILightable.h"
#include "../Interface/SolidLight.h"
#include "../Interface/DuoToneLight.h"
#include "../Interface/WrapperLight.h"
#include "../Interface/BootAnimationLight.h"

class LightFactory
{
public:
    LightFactory()
    {
    }

    ~LightFactory()
    {
        if (light)
        {
            delete[] light;
            light = NULL;
        }
    }

    ILightable *getLight(LightType type)
    {
        if (type == Solid)
            return new SolidLight(43, 31, 1);
        if (type == Boot)
            return new BootAnimationLight();
        else
            return NULL;
    }

    ILightable *getLight(LightType type, JsonObject configuration)
    {
        if (type == Solid)
            return new SolidLight(configuration["r"], configuration["g"], configuration["b"]);
        if (type == DuoTone)
            return new DuoToneLight(configuration);
        if (type == Wrapper)
            return new WrapperLight(configuration);
        if (type == Gradient)
            return new SolidLight(configuration["r"], configuration["g"], configuration["b"]);
        else
            return NULL;
    }

    ILightable *light;

    int randomNumber(int low, int high)
    {
        return rand() % (high - low) + low;
    }
};