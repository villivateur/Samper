#include "battery_monitor.h"
#include "system.h"
#include "pin_definitions.h"


QueueHandle_t batteryQueue;

void BatteryMonitor::Create(ParamManager* pm)
{
    this->pm = pm;

    adcVoltage = 1090;
    batteryVoltage = 12000;
    lowVoltageThr = 10800;

    pm->Bind_i32(0x300, &adcVoltage);
    pm->Bind_i32(0x301, &batteryVoltage);
    pm->Bind_i32(0x302, &lowVoltageThr);
}

void BatteryMonitor::Init()
{
    batteryQueue = xQueueCreate(1, sizeof(int32_t));
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
    int32_t voltage = analogReadMilliVolts(PIN_BAT_ADC);
    xQueueSend(batteryQueue, &voltage, portMAX_DELAY);
}
