
#include <ArduinoJson.h>
#include "./src/Interface/Kernel.h"
#include "./src/Enum/LightType.h"
#include "./src/Config/DeviceConfiguration.h"

Kernel *kernel;

void onMessage(String topic, JsonObject configuration)
{
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
