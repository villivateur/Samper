#pragma once

#include <Arduino.h>
#include "param_manager.h"

class Device
{
public:
    virtual void Create(ParamManager* pm) = 0;
    virtual void Init() = 0;
    virtual void RealtimeCyclic() = 0;
    virtual void NormalCyclic() = 0;

protected:
    ParamManager* pm;
};
