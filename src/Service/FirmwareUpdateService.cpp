#include "../Interface/FirmwareUpdateService.h"

FirmwareUpdateService::FirmwareUpdateService(char *password)
{
    _password = password;
}

void FirmwareUpdateService::start()
{
    Serial.println("Starting service");
    FirmwareUpdateService::setAuthorization(_password);
    FirmwareUpdateService::setExternalRoutes();

    FirmwareUpdateService::onStart();
    FirmwareUpdateService::onEnd();
    FirmwareUpdateService::onProgress();
    FirmwareUpdateService::onError();

    ArduinoOTA.begin();
}

void FirmwareUpdateService::waitForUpdate()
{
    if (_canUpdateFlag)
    {
        uint16_t timeStart = millis();
        Serial.print("Can update for 15 seconds...");
        while (_timeElapsed < 15000)
        {
            ArduinoOTA.handle();
            _timeElapsed = millis() - timeStart;
            delay(10);
        }
        Serial.print("Update period ended");
        _canUpdateFlag = false;
    }

    _server.handleClient();
}

void FirmwareUpdateService::setAuthorization(char *password)
{
    ArduinoOTA.setPassword("admin");
    ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
}

void FirmwareUpdateService::setExternalRoutes()
{
    Serial.println("Setting external routes");

    _server.on("/restart", [this]() {
        Serial.println("RESTART COMMAND");
        _server.send(200, "text/plain", "Restarting...");
        delay(1000);
        ESP.restart();
    });

    _server.on("/upload-firmware", [this]() {
        Serial.println("UPDATE COMMAND");
        _canUpdateFlag = true;
        _server.send(200, "text/plain", "You have 15 seconds to upload your code...");
        _timeElapsed = 0;
    });

    _server.begin();
}

void FirmwareUpdateService::onStart()
{
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
        {
            type = "sketch";
        }
        else
        { // U_SPIFFS
            type = "filesystem";
        }

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);
    });
}

void FirmwareUpdateService::onEnd()
{
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
}

void FirmwareUpdateService::onProgress()
{
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
}

void FirmwareUpdateService::onError()
{
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
        {
            Serial.println("Auth Failed");
        }
        else if (error == OTA_BEGIN_ERROR)
        {
            Serial.println("Begin Failed");
        }
        else if (error == OTA_CONNECT_ERROR)
        {
            Serial.println("Connect Failed");
        }
        else if (error == OTA_RECEIVE_ERROR)
        {
            Serial.println("Receive Failed");
        }
        else if (error == OTA_END_ERROR)
        {
            Serial.println("End Failed");
        }
    });
}