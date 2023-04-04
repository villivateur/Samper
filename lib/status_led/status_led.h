#pragma once

#include <Arduino.h>
#include "device.h"

class StatusLed : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void Reset();
    void RealtimeCyclic();
    void NormalCyclic();

private:
    uint8_t frequecy; // 0.1Hz
    uint8_t duty;

    uint32_t onTickCount;
    uint32_t totalTickCount;
};
