#include "../Interface/SolidLight.h"

SolidLight::SolidLight() : ILightable() {}

SolidLight::SolidLight(int red, int green, int blue) : ILightable()
{
    DynamicJsonDocument doc(4096);
    JsonObject root = doc.to<JsonObject>();

    JsonArray configurationArray = root.createNestedArray("configs");

    for (int i = 0; i < 15; i++)
    {
        JsonObject configurationObject = configurationArray.createNestedObject();
        configurationObject["r"] = red;
        configurationObject["g"] = green;
        configurationObject["b"] = blue;
    }

    _configuration = root;
}

SolidLight::SolidLight(JsonObject configuration) : ILightable()
{
    _configuration = configuration;
}

void SolidLight::start()
{
    _pixels.clear();
    
    int length = _pixels.numPixels();

    for (int i = 0; i < length; i++)
    {
        _pixels.setPixelColor(i, _pixels.Color(
                                     _configuration["configs"][0]["r"],
                                     _configuration["configs"][0]["g"],
                                     _configuration["configs"][0]["b"]
                                     ));
       
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