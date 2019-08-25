#include "../Enum/LightType.h"
#include "../Interface/ILightable.h"
#include "../Interface/SolidLight.h"

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
            return new SolidLight(randomNumber(0, 255), randomNumber(0, 255), randomNumber(0, 255));
        // else if (type == VT_ThreeWheeler)
        //     return new ThreeWheeler();
        // else if (type == VT_FourWheeler)
        //     return new FourWheeler();
        else
            return NULL;
    }

    ILightable *light;

    int randomNumber(int low, int high)
    {
        return rand() % (high - low) + low;
    }
};