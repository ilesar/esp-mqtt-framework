#include "../Interface/TransitionLight.h"

TransitionLight::TransitionLight() : ILightable() {}

TransitionLight::TransitionLight(JsonArray config) : ILightable()
{
    _config = config;
}

void TransitionLight::start()
{
    int length = _pixels.numPixels();
    int i = 0;

    for (i; i <= length / 2; i++)
    {
        _pixels.setPixelColor(i, _pixels.Color(
                                     _config["start"]["r"],
                                     _config["start"]["g"],
                                     _config["start"]["b"]));
    }

    for (i = i; i < length; i++)
    {
        _pixels.setPixelColor(i, _pixels.Color(
                                     _config["end"]["r"],
                                     _config["end"]["g"],
                                     _config["end"]["b"]));
    }

    _pixels.show();
}

void TransitionLight::stop()
{
}