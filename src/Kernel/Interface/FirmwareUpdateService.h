#ifndef FIRMWARE_UPDATE_SERVICE
#define FIRMWARE_UPDATE_SERVICE
 
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <Arduino.h>
#include "../Interface/IKernelService.h"

class FirmwareUpdateService : public  IKernelService
{
public:
    FirmwareUpdateService(char *password);
    FirmwareUpdateService(const FirmwareUpdateService &) = delete;
    void setup();
    void loop();

private:
    char *_password;
    bool _canUpdateFlag = false;
    uint16_t _timeElapsed = 0;
    ESP8266WebServer _server;

    void setAuthorization(char *password);
    void setExternalRoutes();
    void onStart();
    void onProgress();
    void onEnd();
    void onError();
};

#endif