#include "../Interface/BootAnimationLight.h"

BootAnimationLight::BootAnimationLight() : ILightable() {}

BootAnimationLight::BootAnimationLight(JsonObject configuration) : ILightable()
{
    _configuration = configuration;
}

void BootAnimationLight::start()
{
    int length = _pixels.numPixels();

    for (int i = 0; i <= 255; i++)
    {
        for (int j = 0; j < length; j++)
        {
        _pixels.setPixelColor(j, _pixels.Color(0, i, 0));
        }
        _pixels.show();
        delay(20);
    }
}

void BootAnimationLight::stop()
{
    // int length = _pixels.numPixels();

    // for (int i = 255; i >= 0; i--)
    // {
    //     for (int j = 0; j < length; j++)
    //     {
    //         _pixels.setPixelColor(j, _pixels.Color(0, i, 0));
    //     }
    //     _pixels.show();
    //     delay(20);
    // }
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