#ifndef WIRELESS_NETWORKING_SERVICE
#define WIRELESS_NETWORKING_SERVICE

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "../Interface/IKernelService.h"

class WirelessNetworkingService : public IKernelService
{
public:
    WirelessNetworkingService(char *ssid, char *password);
    WirelessNetworkingService(const WirelessNetworkingService &) = delete;
    void setup();

private:
    char *_ssid;
    char *_password;

    void setMode();
    void setAccessPoints();
    void init();
    
};

#endif