#ifndef SMART_HOME_KERNEL
#define SMART_HOME_KERNEL

#include "./Interface/WirelessNetworkingService.h"
#include "./Interface/FirmwareUpdateService.h"
#include "./Interface/MqttService.h"
#include "../Interface/IModule.h"

#define WIFI_SSID "The Mainframe"
#define WIFI_PASSWORD "probajpogoditkoja"
#define FIRMWARE_PASSWORD "admin"
#define MQTT_HOST "mqtt-broker.smarthome.lan"
// #define MQTT_HOST "192.168.31.125"
#define MQTT_PORT 1883

#define CONFIGURATION_CALLBACK void (*configurationCallback)(JsonObject configuration)
#define ACTION_CALLBACK void (*actionCallback)(JsonObject configuration)

class Kernel
{
public:
    Kernel(IModule* device, CONFIGURATION_CALLBACK, ACTION_CALLBACK);
    MqttService *_mqtt;
    FirmwareUpdateService *_firmware;
    WirelessNetworkingService *_wifi;
    void loop();

private:
    void init();
    void (*_configurationCallback)(JsonObject configuration);
    void (*_actionCallback)(JsonObject configuration);

    IModule* _deviceModule;
};

#endif