#include "../Interface/ILightable.h"

ILightable::ILightable()
{

}

void ILightable::start()
{
}

void ILightable::stop()
{
}

void ILightable::setPixels(Adafruit_NeoPixel *pixels)
{
    _pixels = *pixels;
}