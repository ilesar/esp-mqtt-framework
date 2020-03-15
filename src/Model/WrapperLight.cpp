#include "../Interface/WrapperLight.h"

WrapperLight::WrapperLight() : ILightable() {}

WrapperLight::WrapperLight(JsonObject config) : ILightable()
{
    _config = config;
}

void WrapperLight::start()
{
    Serial.println("ENTER");
    int length = _pixels.numPixels();
    Serial.println("numpix");
    Serial.println(length);
    int i = 0;

    for (i; i < length; i++)
    {
        _pixels.setPixelColor(i, _pixels.Color(
                                    _config["inner"]["r"],
                                    _config["inner"]["g"],
                                    _config["inner"]["b"]));
    }
    
    _pixels.setPixelColor(0, _pixels.Color(
                                    _config["outer"]["r"],
                                    _config["outer"]["g"],
                                    _config["outer"]["b"]));
    _pixels.setPixelColor(length - 1, _pixels.Color(
                                    _config["outer"]["r"],
                                    _config["outer"]["g"],
                                    _config["outer"]["b"]));

    _pixels.show();
}

void WrapperLight::stop()
{
}

void WrapperLight::parse(char *data, char *array[])
{
    int i = 0;
    array[i] = strtok(data, "/");

    while (array[i] != NULL)
    {
        array[++i] = strtok(NULL, "/");
    }
}