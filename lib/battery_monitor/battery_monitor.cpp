#include "battery_monitor.h"
#include "system.h"
#include "pin_definitions.h"


QueueHandle_t batteryQueue;

void BatteryMonitor::Create(ParamManager* pm)
{
    this->pm = pm;

    pm->Bind_u32(0x300, &adcVoltage);
    pm->Bind_u32(0x301, &batteryVoltage);
}

void BatteryMonitor::Init()
{
    batteryQueue = xQueueCreate(1, sizeof(uint32_t));
    analogReadResolution(12);

    Reset();
}

void BatteryMonitor::Reset()
{
    xQueueReset(batteryQueue);
}

void BatteryMonitor::RealtimeCyclic()
{
    xQueueReceive(batteryQueue, &adcVoltage, 0);
    batteryVoltage = adcVoltage * 11;
}

void BatteryMonitor::NormalCyclic()
{
    WAIT_RUN_PERIOD_NORMAL_CYCLE(2000);
    uint32_t voltage = analogReadMilliVolts(PIN_BAT_ADC);
    xQueueSend(batteryQueue, &voltage, portMAX_DELAY);
}
