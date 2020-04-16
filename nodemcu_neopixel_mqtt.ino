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

#define DEVICE_ID "home/tv/light/"
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

// JsonArray parsePayload(uint8_t *payload, unsigned int length)
// {
//   payload[length] = '\0';
//   String message = (char *)payload;

//   DynamicJsonDocument doc(4096);
//   auto error = deserializeJson(doc, message);

//   if (error)
//   {
//     Serial.print(F("deserializeJson() failed with code "));
//     Serial.println(error.c_str());
//   }

//   Serial.println("message");
//   Serial.println(message);
//   Serial.println("doc");
//   serializeJson(doc, Serial);
//   Serial.println("");
//   JsonArray lightConfiguration = doc.as<JsonArray>();
//   JsonObject test = doc.as<JsonObject>();

//   Serial.println("PAYLOAD TEST");
//   serializeJson(test, Serial);
//   Serial.println("");
//   return lightConfiguration;
// }

// String parseTopic(char *topic)
// {
//   return (String)topic;
// }

void onMqttMessage(char *charTopic, uint8_t *payload, unsigned int length)
{
  // digitalWrite(2, LOW);
  // Serial.println("GOT MESSAGE");
  // String topic = parseTopic(charTopic);
  // JsonArray configuration = parsePayload(payload, length);

  // Serial.println("callings");
  // if (topic == "home/tv/light/solid")
  // {
  //   led.applyPreset(Solid, configuration);
  // }

  // if (topic == "home/tv/light/transition")
  // {
  //   led.applyPreset(Transition, configuration);
  // }
}

void kernelSetup()
{
  Serial.println("WIFI SETUP...");
  wifi.connect();
  Serial.println("MQTT SETUP...");
  mqtt.setup(onMqttMessage);
  mqtt.connect();
  Serial.println("FIRMWARE UPDATE SETUP...");
  firmwareUpdate.setup();
}

void kernelLoop()
{
  firmwareUpdate.waitForUpdate();
  mqtt.loop();
}

void setup()
{
  // pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("STARTED");
  delay(1000);
  led.connect();
  led.applyPreset(Solid);
  // led.applyPreset(Solid);
  // Serial.begin(115200);
  // delay(1000);
  Serial.println("KERNEL SETUP...");
  kernelSetup();
  led.applyPreset(Boot);

  delay(10);
}

void loop()
{
  kernelLoop();
  // digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  // delay(1000);                     // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  // delay(1000);
  delay(10);
}
