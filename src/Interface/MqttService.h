#ifndef MQTT_SERVICE
#define MQTT_SERVICE

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

class MqttService
{
public:
    MqttService();
   
private:
    Adafruit_NeoPixel _pixels;
    int _pin;
    int _length;
    LightFactory *_lightFactory;
    ILightable *_light;
};

#endif