#pragma once

#include <Arduino.h>
#include "device.h"

class Headlight : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void Reset();
    void RealtimeCyclic();
    void NormalCyclic();

private:
    uint8_t on;
};
