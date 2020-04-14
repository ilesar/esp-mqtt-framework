#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "./src/Interface/WirelessNetworkingService.h"
#include "./src/Interface/LedStripService.h"
#include "./src/Interface/FirmwareUpdateService.h"
#include "./src/Interface/MqttService.h"
#include "./src/Interface/SolidLight.h"
#include "./src/Enum/LightType.h"
#define INT2POINTER(a) ((char *)(intptr_t)(a))

#define LED_PIN 5
#define LED_COUNT 15
#define WIFI_SSID "The Mainframe"
#define WIFI_PASSWORD "probajpogoditkoja"
#define FIRMWARE_PASSWORD "admin"
#define MQTT_HOST "192.168.31.125"
#define MQTT_PORT 1883

MqttService mqtt(MQTT_HOST, MQTT_PORT);
FirmwareUpdateService firmwareUpdate(FIRMWARE_PASSWORD);
LedStripService led(LED_PIN, LED_COUNT);
WirelessNetworkingService wifi(WIFI_SSID, WIFI_PASSWORD);

void onMqttMessage(char *topic, byte *payload, unsigned int length)
{
  String topicStr = topic;
  payload[length] = '\0';
  String message = (char *)payload;

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, message);
  JsonObject lightConfiguration = doc.as<JsonObject>();

  if (topicStr == "home/tv/light/solid")
  {
    led.applyPreset(Solid, lightConfiguration);
  }

  if (topicStr == "home/tv/light/duotone")
  {
    led.applyPreset(DuoTone, lightConfiguration);
  }

  if (topicStr == "home/tv/light/wrapper")
  {
    led.applyPreset(Wrapper, lightConfiguration);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  led.connect();
  led.applyPreset(Solid);
  wifi.connect();
  mqtt.setup(onMqttMessage);
  firmwareUpdate.start();
  led.applyPreset(Boot);

  delay(10);
}

int16_t lastMemorizedTime = 0;

void loop()
{
  firmwareUpdate.waitForUpdate();
  mqtt.loop();
  
  delay(10);
}
