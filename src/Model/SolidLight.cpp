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

SolidLight::SolidLight(JsonObject &configuration) : ILightable()
{
    _configuration = configuration;
}

void SolidLight::start()
{
    _pixels.clear();

    int length = _pixels.numPixels();

    serializeJson(_configuration, Serial);

    for (int i = 0; i < length; i++)
    {
        _pixels.setPixelColor(i, _pixels.Color(
                                     _configuration["configs"][i]["r"],
                                     _configuration["configs"][i]["g"],
                                     _configuration["configs"][i]["b"]));

        delay(10);
    }

    _pixels.show();
}

void SolidLight::stop()
{
    int length = _pixels.numPixels();
    bool hasLivePixel = true;

    while(hasLivePixel == true) {

        hasLivePixel = false;

        for (int i = 0; i < length; i++)
        {
            long color = _pixels.getPixelColor(i);
            Serial.println("COLOR");
            Serial.println(color);
            int red = dimChannel((uint8_t)((color >> 16) & 0xff));
            int green = dimChannel((uint8_t)((color >> 8) & 0xff));
            int blue = dimChannel((uint8_t)(color & 0xff));

            if (red != 0 || green != 0 || blue != 0) {
                hasLivePixel = true;
            }

            _pixels.setPixelColor(i, _pixels.Color(red, green, blue));
        }

        _pixels.show();
        delay(10);
    }
}

int SolidLight::dimChannel(int color)
{
    return constrain(color - 1, 0, 255);
}