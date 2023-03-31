#pragma once

#include <Arduino.h>
#include "device.h"

class Motor : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void RealtimeCyclic();
    void NormalCyclic();
private:
    uint8_t forwardFrac;
    uint8_t leftFrac;
    uint8_t rightFrac;
    uint8_t backFrac;
    uint8_t velocity;
};
