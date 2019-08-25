#ifndef WIRELESS_NETWORKING_SERVICE
#define WIRELESS_NETWORKING_SERVICE

#include <ESP8266WiFi.h>
#include <Arduino.h>

class WirelessNetworkingService
{
public:
    WirelessNetworkingService(char *ssid, char *password);
    bool connect();

private:
    char *_ssid;
    char *_password;

    void setMode();
    void setAccessPoints();
    void init();
    
};

#endif