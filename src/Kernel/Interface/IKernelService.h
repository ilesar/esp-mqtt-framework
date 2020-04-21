#ifndef IKERNELSERVICE_INTERFACE
#define IKERNELSERVICE_INTERFACE

#include <Arduino.h>

class IKernelService
{
public:
    IKernelService();
    virtual void setup();
    virtual void loop();

protected:
};

#endif
