#include "../Interface/IModule.h"

IModule::IModule() {}

IModule::IModule(char *deviceId)
{
    _deviceId = deviceId;
}

void IModule::setConfiguration(JsonObject &configuration)
{
    _configuration = configuration;
}

JsonObject IModule::getConfiguration()
{
    return _configuration;
}

char *IModule::getDeviceId() {
    return _deviceId;
}

void IModule::setDefaultConfiguration() {

}

JsonObject IModule::getDefaultConfiguration()
{
    return _defaultConfiguration;
}