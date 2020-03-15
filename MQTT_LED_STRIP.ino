#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "./src/Interface/WirelessNetworkingService.h"
#include "./src/Interface/LedStripService.h"
#include "./src/Interface/SolidLight.h"
#include "./src/Enum/LightType.h"
#define INT2POINTER(a) ((char *)(intptr_t)(a))

#define LED_PIN 5
#define LED_COUNT 15
const char *mqtt_server = "192.168.31.125";
bool flaggy = false;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
LedStripService led(LED_PIN, LED_COUNT);
// WirelessNetworkingService wifi("The Guest Mainframe", "guestguestguest");
WirelessNetworkingService wifi("The Mainframe", "probajpogoditkoja");

void callback(char *topic, byte *payload, unsigned int length)
{
  String topicStr = topic;
  payload[length] = '\0';
  String message = (char *)payload;

  if (topicStr != "home/tv/light/solid")
  {
    return;
  }

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, message);
  JsonObject obji = doc.as<JsonObject>();

  int redValue = obji["r"];
  int greenValue = obji["g"];
  int blueValue = obji["b"];

  if (message == "1")
  {
    led.applyPreset(Solid);
  }

  if (message == "2")
  {
    led.applyPreset(SolidTwo);
  }

  if (message == "3")
  {
    led.applyPreset(Blue);
  }

  if (message == "4")
  {
    led.applyPreset(Yellow);
  }

  // if (topicStr == "test/message")
  // {
  // if ((char)payload[0] == '1')
  // {
  //   led.applyPreset(Solid);
  // }

  // if ((char)payload[0] == '2')
  // {
  //   led.applyPreset(SolidTwo);
  // }

  // if ((char)payload[0] == '3')
  // {
  //   led.applyPreset(Blue);
  // }

  // if ((char)payload[0] == '4')
  // {
  //   led.applyPreset(Yellow);
  // }
  // }

  // char *message = "";
  // int i = 0;

  // for (i; i < length; i++)
  // {
  //   strcat(message, (char *)&payload[0]);
  // }
  // message[i] = '\0';

  // if (strcmp(message, "blue") == 0)
  // {
  //   led.applyPreset(Blue);
  // }
  // if (strcmp(message, "green") == 0)
  // {
  //   led.applyPreset(SolidTwo);
  // }
  // if (strcmp(message, "yellow") == 0)
  // {
  //   led.applyPreset(Yellow);
  // }
  // if (flaggy == false)
  // {
  //   flaggy = true;
  //   // for (int i = 0; i < length; ++i)
  //   // {
  //   //   mqtt.publish("xtra/one", (char *)&payload[i]);
  //   //   // Serial.print((char)payload[i]);
  //   // }
  // mqtt.publish("xtra/one", message);
  // freeStr(&message);
  //   // mqtt.publish("xtra/one", (char *) payload[0]);
  // }

  // mqtt.publish("test/somethingelse", INT2POINTER(length));
  // mqtt.publish("test/somethingelse", reinterpret_cast<const char *>(topic));
  // mqtt.publish("test/somethingelse", (char *)length);
  // mqtt.publish("test/somethingelse", (char *)payload);
  // digitalWrite(2, LOW);
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");
  // for (int i = 0; i < length; i++)
  // {
  //   Serial.print((char)payload[i]);
  // }
  // Serial.println();
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
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ledstrip-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqtt.connect(clientId.c_str()))
    {
      Serial.println("HAS CONNECTED");
      // boolean x = mqtt.subscribe("test/#");
      // Serial.println(x);
      mqtt.subscribe("home/tv/light/#");
      Serial.println("Subscribed to topic");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  led.connect();

  Serial.println("applying preset");
  led.applyPreset(Solid);
  delay(1000);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  wifi.connect();

  mqtt.setServer(mqtt_server, 1883);
  mqtt.setCallback(callback);
  delay(10);
}

void loop()
{
  if (!mqtt.connected())
  {
    reconnect();
    led.applyPreset(SolidTwo);
  }
  mqtt.loop();

  delay(10);
}