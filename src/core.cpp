#include "core.h"


void Core::Init()
{
    pm.Init();
    memset(devices, 0, sizeof(devices));
    deviceCount = 0;
}

void Core::AddDevice(Device* device)
{
    devices[deviceCount] = device;
    deviceCount++;
    device->Create(&pm);
}

void Core::InitDevices()
{
    for (uint32_t i = 0; i < deviceCount; i++) {
        devices[i]->Init();
    }
}

void Core::RealtimeCyclic()
{
    for (uint32_t i = 0; i < deviceCount; i++) {
        devices[i]->RealtimeCyclic();
    }
}

void Core::NormalCyclic()
{
    for (uint32_t i = 0; i < deviceCount; i++) {
        devices[i]->NormalCyclic();
    }
}
