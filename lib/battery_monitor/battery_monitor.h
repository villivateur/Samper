#pragma once

#include <Arduino.h>
#include "device.h"

class BatteryMonitor : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void Reset();
    void RealtimeCyclic();
    void NormalCyclic();

private:
    uint32_t adcVoltage;
    uint32_t batteryVoltage;
};
