#pragma once

#include <Arduino.h>

enum class ParamType : uint8_t
{
    UNDEFINED = 0,
    INT8 = 1,
    UINT8,
    INT32,
    UINT32,
};

enum class ParamCommand : uint8_t
{
    READ_CMD = 2,
    READ_RESP = 3,

    WRITE_CMD = 4,
    WRITE_RESP = 5,
};

struct ParamAction
{
    ParamCommand cmd;
    uint16_t index;
    uint8_t buf[8];
};

class ParamManager
{
public:
    void Init();
    
    void Bind_u8(uint16_t index, uint8_t* buf);
    void Bind_i32(uint16_t index, int32_t* buf);
    void Bind_u32(uint16_t index, uint32_t* buf);
    
    void Set_u8(uint16_t index, uint8_t val);
    void Set_i32(uint16_t index, int32_t val);
    void Set_u32(uint16_t index, uint32_t val);
    
    uint8_t Get_u8(uint16_t index);
    int32_t Get_i32(uint16_t index);
    uint32_t Get_u32(uint16_t index);

    ParamType GetType(uint16_t index);

    QueueHandle_t paramDownloadQueue;
    QueueHandle_t paramUploadQueue;

private:
};
