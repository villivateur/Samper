#include "beep.h"
#include "system.h"
#include "pin_definitions.h"



void Beep::Create(ParamManager* pm)
{
    this->pm = pm;

    frequecy = 1;
    duty = 0;

    pm->Bind_u8(0x210, &frequecy);
    pm->Bind_u8(0x211, &duty);
}

void Beep::Init()
{
    pinMode(PIN_BEEP, OUTPUT);

    Reset();
}

void Beep::Reset()
{
    digitalWrite(PIN_BEEP, LOW);
    beepTickCount = 0;
    totalTickCount = 0;
}

void Beep::RealtimeCyclic()
{
    // Serial.print(frequecy);
    // Serial.print(";");
    // Serial.println(duty);
    if (frequecy == 0) {
        return;
    }
    
    uint32_t totalTickDemand = (10000 / frequecy) / REALTIME_CYCLE_MS;
    uint32_t beepTickDemand = totalTickDemand * duty / 100;

    if (beepTickCount < beepTickDemand) {
        if (digitalRead(PIN_BEEP) == LOW) {
            digitalWrite(PIN_BEEP, HIGH);
        }
        beepTickCount++;
    } else {
        if (digitalRead(PIN_BEEP) == HIGH) {
            digitalWrite(PIN_BEEP, LOW);
        }
    }
    totalTickCount++;
    if (totalTickCount >= totalTickDemand) {
        beepTickCount = 0;
        totalTickCount = 0;
    }
}

void Beep::NormalCyclic()
{

}
