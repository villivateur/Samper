#pragma once

#include <Arduino.h>
#include "param_manager.h"
#include "device.h"
#include "service.h"

class Core
{
public:
    void Init();

    void AddDevice(Device* device);
    void InitDevices();

    void RealtimeCyclic();
    void NormalCyclic();

private:
    ParamManager pm;
    SamperService service = SamperService(&pm);
    Device* devices[16];
    uint32_t deviceCount;
};
