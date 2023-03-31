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

void ParamManager::Bind_i8(uint16_t index, int8_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::INT8;
}

void ParamManager::Bind_u8(uint16_t index, uint8_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::UINT8;
}

void ParamManager::Bind_i16(uint16_t index, int16_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::INT16;
}

void ParamManager::Bind_u16(uint16_t index, uint16_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::UINT16;
}

void ParamManager::Bind_i32(uint16_t index, int32_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::INT32;
}

void ParamManager::Bind_u32(uint16_t index, uint32_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::UINT32;
}

void ParamManager::Bind_str(uint16_t index, uint8_t* buf)
{
    paramMap[index].buf = buf;
    paramMap[index].type = ParamType::STRING;
}

void ParamManager::Set_i8(uint16_t index, int8_t val)
{
    if (GetType(index) != ParamType::INT8) {
        return;
    }
    *(int8_t*)(paramMap[index].buf) = val;
}

void ParamManager::Set_u8(uint16_t index, uint8_t val)
{
    if (GetType(index) != ParamType::UINT8) {
        return;
    }
    *(uint8_t*)(paramMap[index].buf) = val;
}

void ParamManager::Set_i16(uint16_t index, int16_t val)
{
    if (GetType(index) != ParamType::INT16) {
        return;
    }
    *(int16_t*)(paramMap[index].buf) = val;
}

void ParamManager::Set_u16(uint16_t index, uint16_t val)
{
    if (GetType(index) != ParamType::UINT16) {
        return;
    }
    *(uint16_t*)(paramMap[index].buf) = val;
}

void ParamManager::Set_i32(uint16_t index, int32_t val)
{
    if (GetType(index) != ParamType::INT32) {
        return;
    }
    *(int32_t*)(paramMap[index].buf) = val;
}

void ParamManager::Set_u32(uint16_t index, uint32_t val)
{
    if (GetType(index) != ParamType::UINT32) {
        return;
    }
    *(uint32_t*)(paramMap[index].buf) = val;
}

void ParamManager::Set_str(uint16_t index, uint8_t* buf)
{
    if (GetType(index) != ParamType::STRING) {
        return;
    }
    strcpy((char*)(paramMap[index].buf), (char*)buf);
}

int8_t ParamManager::Get_i8(uint16_t index)
{
    if (GetType(index) != ParamType::INT8) {
        return 0;
    }
    return *(uint8_t*)(paramMap[index].buf);
}

uint8_t ParamManager::Get_u8(uint16_t index)
{
    if (GetType(index) != ParamType::UINT8) {
        return 0;
    }
    return *(int8_t*)(paramMap[index].buf);
}

int16_t ParamManager::Get_i16(uint16_t index)
{
    if (GetType(index) != ParamType::INT16) {
        return 0;
    }
    return *(int16_t*)(paramMap[index].buf);
}

uint16_t ParamManager::Get_u16(uint16_t index)
{
    if (GetType(index) != ParamType::UINT16) {
        return 0;
    }
    return *(uint16_t*)(paramMap[index].buf);
}

int32_t ParamManager::Get_i32(uint16_t index)
{
    if (GetType(index) != ParamType::INT32) {
        return 0;
    }
    return *(int32_t*)(paramMap[index].buf);
}

uint32_t ParamManager::Get_u32(uint16_t index)
{
    if (GetType(index) != ParamType::UINT32) {
        return 0;
    }
    return *(uint32_t*)(paramMap[index].buf);
}

void ParamManager::Get_str(uint16_t index, uint8_t* buf)
{
    if (GetType(index) != ParamType::STRING) {
        buf[0] = '\0';
        return;
    }
    strcpy((char*)buf, (char*)(paramMap[index].buf));
}

ParamType ParamManager::GetType(uint16_t index)
{
    return paramMap[index].type;
}

