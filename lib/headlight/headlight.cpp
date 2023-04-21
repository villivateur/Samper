#include "headlight.h"
#include "system.h"
#include "pin_definitions.h"



void Headlight::Create(ParamManager* pm)
{
    this->pm = pm;

    pm->Bind_u8(0x220, &on);
}

void Headlight::Init()
{
    pinMode(PIN_HEADLIGHT, OUTPUT);

    Reset();
}

void Headlight::Reset()
{
    digitalWrite(PIN_HEADLIGHT, LOW);
}

void Headlight::RealtimeCyclic()
{
    if (on) {
        digitalWrite(PIN_HEADLIGHT, HIGH);
    } else {
        digitalWrite(PIN_HEADLIGHT, LOW);
    }
}

void Headlight::NormalCyclic()
{

}
