#include "param_manager.h"


struct ParamInfo
{
    ParamType type;
    void* buf;
};

static ParamInfo paramMap[0x1000];

void ParamManager::Init()
{
    memset(paramMap, 0, sizeof(paramMap));
}

void ParamManager::Bind_u8(uint16_t index, uint8_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::UINT8;
}

void ParamManager::Bind_i32(uint16_t index, int32_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::INT32;
}

void ParamManager::Set_u8(uint16_t index, uint8_t val)
{
    if (GetType(index) != ParamType::UINT8) {
        return;
    }
    *(uint8_t*)(paramMap[index].buf) = val;
}

void ParamManager::Set_i32(uint16_t index, int32_t val)
{
    if (GetType(index) != ParamType::INT32) {
        return;
    }
    *(int32_t*)(paramMap[index].buf) = val;
}

uint8_t ParamManager::Get_u8(uint16_t index)
{
    if (GetType(index) != ParamType::UINT8) {
        return 0;
    }
    return *(int8_t*)(paramMap[index].buf);
}

int32_t ParamManager::Get_i32(uint16_t index)
{
    if (GetType(index) != ParamType::INT32) {
        return 0;
    }
    return *(int32_t*)(paramMap[index].buf);
}

ParamType ParamManager::GetType(uint16_t index)
{
    return paramMap[index].type;
}

