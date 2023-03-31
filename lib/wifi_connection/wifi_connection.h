#pragma once

#include <Arduino.h>
#include "device.h"

class WifiConnection : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void RealtimeCyclic();
    void NormalCyclic();
private:
};
