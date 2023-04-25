#include <Arduino.h>
#include "system.h"
#include "service.h"


SamperService::SamperService(ParamManager* pm)
{
    this->pm = pm;
}

void SamperService::RealtimeCyclic()
{
}

void SamperService::NormalCyclic()
{
    MonitorBattery();
}

void SamperService::MonitorBattery()
{
    WAIT_RUN_PERIOD_NORMAL_CYCLE(2000);

    static uint32_t lowVoltageCount = 0;

    uint32_t voltage = pm->Get_u32(0x301);
    if (voltage < 9500) {
        lowVoltageCount++;
    } else {
        lowVoltageCount = 0;
    }

    if (lowVoltageCount > 3) {
        pm->Set_u8(0x100, 0);
        pm->Set_u8(0x210, 10);
        pm->Set_u8(0x211, 10);
    }
}
