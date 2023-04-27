#include "core.h"


void Core::Init()
{
    pm.Init();
}

void Core::AddDevice(Device* device)
{
    devices.push_back(device);
    device->Create(&pm);
}

void Core::InitDevices()
{
    for (auto device : devices) {
        device->Init();
    }
}

void Core::RealtimeCyclic()
{
    service.RealtimeCyclic();
    for (auto device : devices) {
        device->RealtimeCyclic();
    }
}

void Core::NormalCyclic()
{
    service.NormalCyclic();
    for (auto device : devices) {
        device->NormalCyclic();
    }
}
