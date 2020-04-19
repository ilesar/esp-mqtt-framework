#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "./src/Interface/Kernel.h"
#include "./src/Interface/WirelessNetworkingService.h"
#include "./src/Interface/LedStripService.h"
#include "./src/Interface/FirmwareUpdateService.h"
#include "./src/Interface/MqttService.h"
#include "./src/Interface/SolidLight.h"
#include "./src/Enum/LightType.h"
#define INT2POINTER(a) ((char *)(intptr_t)(a))

#define DEVICE_ID "15ledstrip"

Kernel *kernel;

void onMessage(char *charTopic, uint8_t *payload, unsigned int length)
{
  Serial.println("GOT MESSAGE");
  String topic = (String)charTopic;
  payload[length] = '\0';
  char *message = (char *)payload;

  DynamicJsonDocument doc(4096);
  auto error = deserializeJson(doc, message);

  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
  }

  JsonObject configuration = doc.as<JsonObject>();

  if (topic == DEVICE_ID)
  {
    kernel->_led->applyPreset(Solid, configuration);
  }
}

void setup()
{
  kernel = new Kernel(DEVICE_ID);
  kernel->setup(onMessage);
}

void loop()
{
  kernel->loop();
  delay(10);
}
