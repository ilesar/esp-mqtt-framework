#include "../Interface/WirelessNetworkingService.h"

WirelessNetworkingService::WirelessNetworkingService(char *ssid, char *password)
{
    _ssid = ssid;
    _password = password;
}

bool WirelessNetworkingService::connect()
{
    Serial.println("Enabling wifi...");

    setMode();
    setAccessPoints();
    init();

    // /Users/ivan/Library/Arduino15/packages/esp8266/hardware/esp8266/2.5.0/libraries/ESP8266WiFi/src
}

void WirelessNetworkingService::setMode()
{
    Serial.printf("Wi-Fi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");
}

void WirelessNetworkingService::setAccessPoints()
{
    Serial.println("Setting credentials...");
    WiFi.disconnect();
    delay(3000);
    Serial.print("Connecting...");

    // IPAddress ip(192, 168, 31, 106);
    // IPAddress gw(192, 168, 31, 1);
    // IPAddress sn(255, 255, 255, 0);
    // WiFi.config(ip, gw, sn, gw);

    Serial.println(_ssid);
    Serial.println(_password);
    WiFi.begin(_ssid, _password);
}

void WirelessNetworkingService::init()
{
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println(WiFi.status());
        Serial.print(".");
        delay(1000);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
    delay(1000);
}