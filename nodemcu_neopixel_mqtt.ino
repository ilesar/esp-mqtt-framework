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

#define DEVICE_ID "15ledstrip"
#define LED_PIN 5
#define LED_COUNT 15
#define WIFI_SSID "The Mainframe"
#define WIFI_PASSWORD "probajpogoditkoja"
#define FIRMWARE_PASSWORD "admin"
#define MQTT_HOST "192.168.31.125"
#define MQTT_PORT 1883

MqttService mqtt(MQTT_HOST, MQTT_PORT, DEVICE_ID);
FirmwareUpdateService firmwareUpdate(FIRMWARE_PASSWORD);
LedStripService led(LED_PIN, LED_COUNT);
WirelessNetworkingService wifi(WIFI_SSID, WIFI_PASSWORD);

void onMqttMessage(char *charTopic, uint8_t *payload, unsigned int length)
{
  Serial.println("GOT MESSAGE");
  String topic = (String)charTopic;

  payload[length] = '\0';
  char *message = (char *)payload;

  Serial.println("STRING");
  Serial.println(message);

  DynamicJsonDocument doc(4096);
  auto error = deserializeJson(doc, message);

  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
  }

  JsonObject configuration = doc.as<JsonObject>();

  Serial.println("TOPICO");
  serializeJson(configuration, Serial);
  Serial.println("");

  if (topic == DEVICE_ID)
  {
    led.applyPreset(Solid, configuration);
  }
}

void kernelSetup()
{
  wifi.connect();
  mqtt.setup(onMqttMessage);
  mqtt.connect();
  firmwareUpdate.setup();
}

void kernelLoop()
{
  firmwareUpdate.waitForUpdate();
  mqtt.loop();
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  led.connect();
  led.applyPreset(Solid, true);
  kernelSetup();

  // Serial.begin(115200);
  // delay(1000);

  led.applyPreset(Boot);

  delay(10);
}

void loop()
{
  kernelLoop();
  delay(10);
}
