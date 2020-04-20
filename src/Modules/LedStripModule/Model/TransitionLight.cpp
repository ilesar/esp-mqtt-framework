#include "../Interface/TransitionLight.h"

TransitionLight::TransitionLight() : ILightable() {}

TransitionLight::TransitionLight(JsonObject configuration) : ILightable()
{
    _configuration = configuration;
}

void TransitionLight::start()
{
    // int length = _pixels.numPixels();
    // int i = 0;

    // for (i; i <= length / 2; i++)
    // {
    //     _pixels.setPixelColor(i, _pixels.Color(
    //                                  _configuration["start"]["r"],
    //                                  _configuration["start"]["g"],
    //                                  _configuration["start"]["b"]));
    // }

    // for (i = i; i < length; i++)
    // {
    //     _pixels.setPixelColor(i, _pixels.Color(
    //                                  _configuration["end"]["r"],
    //                                  _configuration["end"]["g"],
    //                                  _configuration["end"]["b"]));
    // }

    // _pixels.show();
}

void TransitionLight::stop()
{
}