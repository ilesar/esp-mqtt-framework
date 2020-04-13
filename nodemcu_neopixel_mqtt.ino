#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "./src/Interface/WirelessNetworkingService.h"
#include "./src/Interface/LedStripService.h"
#include "./src/Interface/FirmwareUpdateService.h"
#include "./src/Interface/SolidLight.h"
#include "./src/Enum/LightType.h"
#define INT2POINTER(a) ((char *)(intptr_t)(a))

#define LED_PIN 5
#define LED_COUNT 15
#define WIFI_SSID "The Mainframe"
#define WIFI_PASSWORD "probajpogoditkoja"
#define FIRMWARE_PASSWORD "admin"

const char *mqtt_server = "192.168.31.125";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
FirmwareUpdateService firmwareUpdate(FIRMWARE_PASSWORD);
LedStripService led(LED_PIN, LED_COUNT);
WirelessNetworkingService wifi(WIFI_SSID, WIFI_PASSWORD);

void callback(char *topic, byte *payload, unsigned int length)
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

void freeStr(char **str)
{
  *str = NULL;
}

char *resolveMessage(byte *message, unsigned int length)
{
  char *temp = "";
  int i = 0;

  for (i; i < length; i++)
  {
    strcat(temp, (char *)&message[0]);
  }
  temp[i] = '\0';

  return temp;
}

void reconnect()
{
  // Loop until we're reconnected
  while (!mqtt.connected())
  {
    String clientId = "ledstrip-";
    clientId += String(random(0xffff), HEX);

    if (mqtt.connect(clientId.c_str()))
    {
     
      mqtt.subscribe("home/tv/light/#");
    }
    else
    {
      // Serial.print("failed, rc=");
      // Serial.print(mqtt.state());

      delay(5000);
    }
  }
}

void setup()
{
  Serial.println("STARTED SERIAL");
  Serial.begin(115200);
  delay(1000);

  Serial.println("SET PIN MODE");
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  Serial.println("CONNECT LED");
  led.connect();

  Serial.println("APPLY PRESET");
  led.applyPreset(Solid);
  Serial.println("PRESET APPLIED");

  

  Serial.println("WIFI CONNECT");
  wifi.connect();

  Serial.println("MQTT SERVER");
  mqtt.setServer(mqtt_server, 1883);
  Serial.println("MQTT CALLBACK");
  mqtt.setCallback(callback);

  Serial.println("FIRMWAREUPDATE");
  firmwareUpdate.start();

  led.applyPreset(Boot);

  delay(10);
}

int16_t lastMemorizedTime = 0;

void loop()
{
  firmwareUpdate.waitForUpdate();
  if (!mqtt.connected())
  {
    reconnect();
  }
  mqtt.loop();
  
  if (millis() - lastMemorizedTime > 200) {
    lastMemorizedTime = millis();
    digitalWrite(2, !digitalRead(2));
  }

  delay(10);
}
