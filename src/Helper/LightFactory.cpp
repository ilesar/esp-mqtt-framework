#include <ArduinoJson.h>
#include "../Enum/LightType.h"
#include "../Interface/ILightable.h"
#include "../Interface/SolidLight.h"
#include "../Interface/TransitionLight.h"
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
    }

    ILightable *getLight(LightType type)
    {
        if (type == Solid)
            return new SolidLight(255, 0, 0);
        if (type == Boot)
            return new BootAnimationLight();
        else
            return NULL;
    }

    ILightable *getLight(LightType type, JsonObject &configuration)
    {
        // Serial.println("TEST");
        // serializeJson(configuration, Serial);

        if (type == Solid)
            return new SolidLight(configuration);
        // if (type == Transition)
        //     return new TransitionLight(configuration);
        // if (type == Wrapper)
        //     return new WrapperLight(configuration);
        // if (type == Gradient)
        //     return new SolidLight(configuration);
        else
            return NULL;
    }

    int randomNumber(int low, int high)
    {
        return rand() % (high - low) + low;
    }
};