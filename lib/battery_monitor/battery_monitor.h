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
    int32_t adcVoltage;
    int32_t batteryVoltage;
    int32_t lowVoltageThr;
};
