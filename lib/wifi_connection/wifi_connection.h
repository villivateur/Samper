#pragma once

#include <Arduino.h>
#include "device.h"

#define UDP_PORT 321
#define UDP_MAX_PACKAGE_SIZE 128

class WifiConnection : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void Reset();
    void RealtimeCyclic();
    void NormalCyclic();

private:
    void ParsePackage(char* package, int len);
    void ParseLine(std::string line);

    uint8_t enable;
    uint8_t udpListening;
};
