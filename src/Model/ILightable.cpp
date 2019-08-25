#include "../Interface/ILightable.h"

ILightable::ILightable()
{

}

void ILightable::start()
{
    Serial.println("Base light STARTED");
}

void ILightable::stop()
{
    Serial.println("Base light STOPPED!!!");
}

void ILightable::setPixels(Adafruit_NeoPixel *pixels)
{
    Serial.println('IN');
    _pixels = *pixels;
    Serial.println('OUT');
}