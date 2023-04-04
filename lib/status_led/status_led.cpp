#include "status_led.h"
#include "system.h"
#include "pin_definitions.h"



void StatusLed::Create(ParamManager* pm)
{
    this->pm = pm;

    frequecy = 1;
    duty = 0;

    pm->Bind_u8(0x200, &frequecy);
    pm->Bind_u8(0x201, &duty);
}

void StatusLed::Init()
{
    pinMode(PIN_STATUS_LED, OUTPUT);

    Reset();
}

void StatusLed::Reset()
{
    digitalWrite(PIN_STATUS_LED, LOW);
    onTickCount = 0;
    totalTickCount = 0;
}

void StatusLed::RealtimeCyclic()
{
    if (frequecy == 0) {
        return;
    }
    
    uint32_t totalTickDemand = (10000 / frequecy) / REALTIME_CYCLE_MS;
    uint32_t onTickDemand = totalTickDemand * duty / 100;

    if (onTickCount < onTickDemand / REALTIME_CYCLE_MS) {
        if (digitalRead(PIN_STATUS_LED) == LOW) {
            digitalWrite(PIN_STATUS_LED, HIGH);
        }
        onTickCount++;
    } else {
        if (digitalRead(PIN_STATUS_LED) == HIGH) {
            digitalWrite(PIN_STATUS_LED, LOW);
        }
    }
    totalTickCount++;
    if (totalTickCount >= totalTickDemand / REALTIME_CYCLE_MS) {
        onTickCount = 0;
        totalTickCount = 0;
    }
}

void StatusLed::NormalCyclic()
{

}
