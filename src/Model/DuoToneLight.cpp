#include "../Interface/DuoToneLight.h"

DuoToneLight::DuoToneLight() : ILightable() {}

DuoToneLight::DuoToneLight(JsonObject config) : ILightable()
{
    _config = config;
}

void DuoToneLight::start()
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

void DuoToneLight::stop()
{
}

void DuoToneLight::parse(char *data, char *array[])
{
    int i = 0;
    array[i] = strtok(data, "/");

    while (array[i] != NULL)
    {
        array[++i] = strtok(NULL, "/");
    }
}