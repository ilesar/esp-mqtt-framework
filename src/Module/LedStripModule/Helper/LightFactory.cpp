#include <ArduinoJson.h>
#include "../Enum/LightType.h"
#include "../Interface/ILightable.h"
#include "../Interface/SolidLight.h"
#include "../Interface/TransitionLight.h"

class LightFactory
{
public:
    LightFactory()
    {
    }

    ~LightFactory()
    {
    }

    ILightable *getLight(LightType type)
    {
        if (type == Solid)
            return new SolidLight(255, 0, 0);
        if (type == Boot)
            return new SolidLight(0, 255, 0);
        else
            return NULL;
    }

    ILightable *getLight(LightType type, JsonObject &configuration)
    {
        if (type == Solid)
            return new SolidLight(configuration);
        // if (type == Transition)
        //     return new TransitionLight(configuration);
        else
            return NULL;
    }

    int randomNumber(int low, int high)
    {
        return rand() % (high - low) + low;
    }
};