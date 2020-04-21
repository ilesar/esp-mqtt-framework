#include "./Kernel.h"

Kernel::Kernel(IModule deviceModule, CONFIGURATION_CALLBACK, ACTION_CALLBACK)
{
    _deviceModule = deviceModule;
    _configurationCallback = configurationCallback;
    _actionCallback = actionCallback;

    _mqtt = new MqttService(MQTT_HOST, MQTT_PORT, _deviceModule.getDeviceId());
    _firmware = new FirmwareUpdateService(FIRMWARE_PASSWORD);
    _wifi = new WirelessNetworkingService(WIFI_SSID, WIFI_PASSWORD);

    init();
}

void Kernel::init()
{
    _wifi->setup();
    _mqtt->setup(_configurationCallback, _actionCallback);
    _firmware->setup();
}

void Kernel::loop()
{
    _firmware->loop();
    _mqtt->loop();
}