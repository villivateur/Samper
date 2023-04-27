#pragma once

#include <Arduino.h>
#include <string>
#include "device.h"


#define I2C_MAX_PACKAGE_SIZE 128

class SamperI2c : public Device
{
public:
    void Create(ParamManager* pm);
    void Init();
    void Reset();
    void RealtimeCyclic();
    void NormalCyclic();

private:
    void ParsePackage(std::string* package);
    void ParseLine(std::string line);
    std::string BuildString(ParamAction* action);
};
