#pragma once

#include "param_manager.h"

class SamperService
{
public:
    SamperService(ParamManager* pm);
    void RealtimeCyclic();
    void NormalCyclic();

private:
    void MonitorBattery();

    ParamManager* pm;
};
