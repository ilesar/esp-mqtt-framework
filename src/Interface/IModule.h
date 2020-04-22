#ifndef IMODULE_INTERFACE
#define IMODULE_INTERFACE

#include <Arduino.h>
#include <ArduinoJson.h>

class IModule
{
public:
    IModule();
    IModule(char *deviceId);
    void setConfiguration(JsonObject &configuration);
    JsonObject getConfiguration();
    char *getDeviceId();
    JsonObject getDefaultConfiguration();

protected:
    virtual void setDefaultConfiguration();
    JsonObject _configuration;
    DynamicJsonDocument doc = DynamicJsonDocument(4096);
    JsonObject _defaultConfiguration;
    char *_deviceId;
    
};

#endif