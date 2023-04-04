#pragma once

#include <Arduino.h>
#include "device.h"

class Motor : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void Reset();
    void RealtimeCyclic();
    void NormalCyclic();
private:
    uint8_t enable;
    uint8_t velocity;
    uint8_t forwardComp;
    uint8_t leftComp;
    uint8_t rightComp;
    uint8_t backComp;
};
