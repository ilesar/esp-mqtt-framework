#include "../Interface/WirelessNetworkingService.h"
#include <ArduinoJson.h>

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
}

void WirelessNetworkingService::setMode()
{
    Serial.printf("Wi-Fi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");
}

void WirelessNetworkingService::setAccessPoints()
{
    Serial.println("Setting credentials...");
    WiFi.disconnect();
    delay(100);
    Serial.print("Connecting...");

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
    delay(10);
}