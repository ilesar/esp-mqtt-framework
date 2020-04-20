#ifndef SMART_HOME_KERNEL
#define SMART_HOME_KERNEL

#include "./Interface/WirelessNetworkingService.h"
#include "./Interface/FirmwareUpdateService.h"
#include "./Interface/MqttService.h"

#define WIFI_SSID "The Mainframe"
#define WIFI_PASSWORD "probajpogoditkoja"
#define FIRMWARE_PASSWORD "admin"
#define MQTT_HOST "192.168.31.125"
#define MQTT_PORT 1883

class Kernel
{
public:
    Kernel(char* deviceId);
    MqttService *_mqtt;
    FirmwareUpdateService *_firmware;
    WirelessNetworkingService *_wifi;

    void setup(void (*messageCallback)(String message, JsonObject configuration));
    void loop();

private:
    char* _deviceId;
};

#endif