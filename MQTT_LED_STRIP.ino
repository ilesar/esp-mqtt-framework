#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#include "./src/Interface/WirelessNetworkingService.h"
#include "./src/Interface/LedStripService.h"
#include "./src/Interface/SolidLight.h"
#include "./src/Enum/LightType.h"


#define LED_PIN 5
#define LED_COUNT 15

WiFiClient wifiClient;
// PubSubClient mqtt(wifiClient);
LedStripService led(LED_PIN, LED_COUNT);
// WirelessNetworkingService wifi("The Guest Mainframe", "guestguestguest");
WirelessNetworkingService wifi("The Mainframe", "probajpogoditkoja");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  led.connect();

  // Serial.println("creating json");
  // char *ycolor = "{\"r\":1,\"g\":2,\"b\":3}";
  // Serial.println("creating color");
  // SolidLight colorPreset = SolidLight(255, 0, 0);
  Serial.println("applying preset");
  led.applyPreset(Solid);
  delay(1000);
  led.applyPreset(SolidTwo);

  pinMode(2, OUTPUT);

  wifi.connect();

  // mqtt.setServer(mqtt_server, 1883);
  // mqtt.setCallback(callback);
}

void loop() {
  // if (!mqtt.connected())
  // {
  //   reconnect();
  // }
  // mqtt.loop();
  digitalWrite(2, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                     // Wait for a second
  digitalWrite(2, HIGH); // Turn the LED off by making the voltage HIGH
  delay(2000);
}
