
#include <ArduinoJson.h>
#include "./src/Kernel/Kernel.h"
#include "./src/Interface/IModule.h"
#include "./src/Module/LedStripModule/LedStripModule.h"
#include "./src/Module/LedStripModule/Enum/LightType.h"

#define DEVICE_ID "15ledstrip"
#define LED_PIN 5
#define LED_COUNT 15

Kernel *kernel;
LedStripModule *led;

void onConfigurationRecieved(JsonObject configuration)
{
  Serial.println("CONFIG");

  led->applyPreset(Solid, configuration);
}

void onActionTriggered(JsonObject configuration)
{
  Serial.println("ACTION");
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  
  led = new LedStripModule(DEVICE_ID, LED_PIN, LED_COUNT);
  
  led->connect();
  // led->applyPreset(Solid, true);

  // Serial.begin(115200);
  // delay(1000);

  kernel = new Kernel(led, onConfigurationRecieved, onActionTriggered);
}

void loop()
{
  kernel->loop();
  delay(10);
}
