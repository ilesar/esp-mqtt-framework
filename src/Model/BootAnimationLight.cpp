#include "../Interface/BootAnimationLight.h"

BootAnimationLight::BootAnimationLight() : ILightable() {}

BootAnimationLight::BootAnimationLight(JsonObject config) : ILightable()
{
    _config = config;
}

void BootAnimationLight::start()
{
    int length = _pixels.numPixels();

    for (int i = 0; i <= 255; i++)
    {
        for (int j = 0; j < length; j++)
        {
        _pixels.setPixelColor(j, _pixels.Color(i, i, i));
        }
        _pixels.show();
        delay(5);
    }
}

void BootAnimationLight::stop()
{
}

void BootAnimationLight::parse(char *data, char *array[])
{
    int i = 0;
    array[i] = strtok(data, "/");

    while (array[i] != NULL)
    {
        array[++i] = strtok(NULL, "/");
    }
}