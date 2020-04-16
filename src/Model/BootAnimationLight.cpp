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
    int length = _pixels.numPixels();
    bool hasLivePixel = true;

    while (hasLivePixel == true)
    {

        hasLivePixel = false;

        for (int i = 0; i < length; i++)
        {
            long color = _pixels.getPixelColor(i);
            int red = dimChannel((uint8_t)((color >> 16) & 0xff));
            int green = dimChannel((uint8_t)((color >> 8) & 0xff));
            int blue = dimChannel((uint8_t)(color & 0xff));

            if (red != 0 || green != 0 || blue != 0)
            {
                hasLivePixel = true;
            }

            _pixels.setPixelColor(i, _pixels.Color(red, green, blue));
        }

        _pixels.show();
        delay(3);
    }
}

int BootAnimationLight::dimChannel(int color)
{
    return constrain(color - 1, 0, 255);
}