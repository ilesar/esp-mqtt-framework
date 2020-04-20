#include "./Kernel.h"

Kernel::Kernel(char* deviceId)
{
    _deviceId = deviceId;

    _mqtt = new MqttService(MQTT_HOST, MQTT_PORT, _deviceId);
    _firmware = new FirmwareUpdateService(FIRMWARE_PASSWORD);
    _wifi = new WirelessNetworkingService(WIFI_SSID, WIFI_PASSWORD);
}

void Kernel::setup(void (*callback)(String message, JsonObject configuration))
{
    _wifi->connect();
    _mqtt->setup(callback);
    _mqtt->connect();
    _mqtt->install();
    _firmware->setup();
}

void Kernel::loop()
{
    _firmware->waitForUpdate();
    _mqtt->loop();
}