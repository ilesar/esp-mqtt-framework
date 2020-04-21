#ifndef IMODULE_INTERFACE
#define IMODULE_INTERFACE

#include <Arduino.h>
#include <ArduinoJson.h>

class IModule
{
public:
    IModule();
    IModule(char *deviceId);
    virtual void setConfiguration(JsonObject &configuration);
    virtual JsonObject getConfiguration();
    virtual char *getDeviceId();

protected:
    virtual void applyDefaultConfiguration();
    JsonObject _configuration;
    char *_deviceId;
};

#endif