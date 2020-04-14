#include "../Interface/SolidLight.h"

SolidLight::SolidLight() : ILightable() {}

SolidLight::SolidLight(int red, int green, int blue) : ILightable()
{
    _r = red;
    _g = green;
    _b = blue;
}

void SolidLight::start()
{
    int length = _pixels.numPixels();
    for (int i = 0; i < length; i++)
    {
        _pixels.setPixelColor(i, _pixels.Color(_r, _g, _b));
        delay(10);
    }

    _pixels.show();
}

void SolidLight::stop()
{
    // int length = _pixels.numPixels();

    // while (_r != 0 || _g != 0 || _b != 0)
    // {
    //     if (_r > 0)
    //     {
    //         _r--;
    //     }

    //     if (_g > 0)
    //     {
    //         _g--;
    //     }

    //     if (_b > 0)
    //     {
    //         _b--;
    //     }

    //     for (int j = 0; j < length; j++)
    //     {
    //         _pixels.setPixelColor(j, _pixels.Color(_r, _g, _b));
    //     }
    //     _pixels.show();
    //     delay(20);
    // }
}

void SolidLight::parse(char *data, char *array[])
{
    int i = 0;
    array[i] = strtok(data, "/");

    while (array[i] != NULL)
    {
        array[++i] = strtok(NULL, "/");
    }
}