#pragma once

#include <Arduino.h>

enum class ParamType : uint8_t
{
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    INT64,
    UINT64,
    STRING,
};

class ParamManager
{
public:
    void Init();
    
    void Bind_i8(uint16_t index, int8_t* buf);
    void Bind_u8(uint16_t index, uint8_t* buf);
    void Bind_i16(uint16_t index, int16_t* buf);
    void Bind_u16(uint16_t index, uint16_t* buf);
    void Bind_i32(uint16_t index, int32_t* buf);
    void Bind_u32(uint16_t index, uint32_t* buf);
    void Bind_str(uint16_t index, uint8_t* buf);
    
    void Set_i8(uint16_t index, int8_t val);
    void Set_u8(uint16_t index, uint8_t val);
    void Set_i16(uint16_t index, int16_t val);
    void Set_u16(uint16_t index, uint16_t val);
    void Set_i32(uint16_t index, int32_t val);
    void Set_u32(uint16_t index, uint32_t val);
    void Set_str(uint16_t index, uint8_t* buf);
    
    int8_t Get_i8(uint16_t index);
    uint8_t Get_u8(uint16_t index);
    int16_t Get_i16(uint16_t index);
    uint16_t Get_u16(uint16_t index);
    int32_t Get_i32(uint16_t index);
    uint32_t Get_u32(uint16_t index);
    void Get_str(uint16_t index, uint8_t* buf);

    ParamType GetType(uint16_t index);

private:

};
