
#include <ArduinoJson.h>
#include "./src/Kernel/Kernel.h"
#include "./src/Modules/LedStripModule/LedStripModule.h"
#include "./src/Modules/LedStripModule/Enum/LightType.h"
#include "./src/Config/DeviceConfiguration.h"


Kernel *kernel;
LedStripModule led(LED_PIN, LED_COUNT);


void onInit() {
  Serial.begin(115200);
  delay(100);

  led.connect();
  led.applyPreset(Solid, true);
}

void onMessage(String topic, JsonObject configuration)
{
  if (topic == DEVICE_ID)
  {
    led.applyPreset(Solid, configuration);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  onInit();
  
  kernel = new Kernel(DEVICE_ID);
  kernel->setup(onMessage);
}

void loop()
{
  kernel->loop();
  delay(10);
}
