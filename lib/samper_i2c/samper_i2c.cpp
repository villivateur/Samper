#include "samper_i2c.h"
#include <Wire.h>
#include <sstream>
#include <vector>
#include "string_utils.h"


static QueueHandle_t normal2realtimeQueue;
static QueueHandle_t realtime2normalQueue;
static QueueHandle_t app2driverQueue;
static QueueHandle_t driver2appQueue;

void OnI2cRequest()
{
    char ch = 0;
    while (xQueueReceive(app2driverQueue, &ch, 0)) {
        Wire.print(ch);
    }
}

void OnI2cReceive(int len)
{
    while (Wire.available()) {
        char ch = (char)Wire.read();
        if (ch != 0x00) {
            xQueueSend(driver2appQueue, &ch, portMAX_DELAY);
        }
    }
}

void SamperI2c::Create(ParamManager* pm)
{
    this->pm = pm;
    Wire.onRequest(OnI2cRequest);
    Wire.onReceive(OnI2cReceive);
}

void SamperI2c::Init()
{
    normal2realtimeQueue = xQueueCreate(32, sizeof(ParamAction));
    realtime2normalQueue = xQueueCreate(32, sizeof(ParamAction));
    app2driverQueue = xQueueCreate(64, sizeof(uint8_t));
    driver2appQueue = xQueueCreate(64, sizeof(uint8_t));

    Wire.begin(0x27);
}

void SamperI2c::Reset()
{
}

void SamperI2c::RealtimeCyclic()
{
    ParamAction reqeust = {};
    while (xQueueReceive(normal2realtimeQueue, &reqeust, 0)) {
        switch (reqeust.cmd) {
            case ParamCommand::WRITE_CMD: {
                switch (pm->GetType(reqeust.index)) {
                    case ParamType::UINT8: {
                        pm->Set_u8(reqeust.index, *(uint8_t*)(reqeust.buf));
                    } break;
                    case ParamType::INT32: {
                        pm->Set_i32(reqeust.index, *(int32_t*)(reqeust.buf));
                    } break;
                    default:
                        break;
                }
                ParamAction response;
                response.cmd = ParamCommand::WRITE_RESP;
                response.index = reqeust.index;
                xQueueSend(realtime2normalQueue, &response, 0);
            } break;
            case ParamCommand::READ_CMD: {
                ParamAction response;
                response.cmd = ParamCommand::READ_RESP;
                response.index = reqeust.index;
                switch (pm->GetType(reqeust.index)) {
                    case ParamType::UINT8: {
                        *(uint8_t*)response.buf = pm->Get_u8(reqeust.index);
                    } break;
                    case ParamType::INT32: {
                        *(int32_t*)response.buf = pm->Get_i32(reqeust.index);
                    } break;
                    default:
                        break;
                }
                xQueueSend(realtime2normalQueue, &response, 0);
            } break;
            default:
                break;
        }
    }
}

void SamperI2c::NormalCyclic()
{
    ParamAction response;

    while (xQueueReceive(realtime2normalQueue, &response, 0)) {
        std::string str = BuildString(&response);
        for (char& c : str) {
            xQueueSend(app2driverQueue, &c, portMAX_DELAY);
        }
    }

    static std::string package;
    char tempChar = 0;
    while (xQueueReceive(driver2appQueue, &tempChar, 0)) {
        package += tempChar;
    }
    if (package.length() > 0) {
        ParsePackage(&package);
    }
}

void SamperI2c::ParsePackage(std::string* package)
{
    bool packageNotEnd = false;

    // Get last no-space char
    char lastChar;
    uint32_t i = package->length() - 1;
    lastChar = (*package)[i];
    while (std::isspace(lastChar) && (i != 0)) {
        i--;
        lastChar = (*package)[i];
    }
    if (lastChar != ';') {
        packageNotEnd = true;
    }

    std::vector<std::string> lines;
    std::istringstream f(*package);
    std::string s;    
    while (getline(f, s, ';')) {
        lines.push_back(s);
    }
    package->clear();
    if (packageNotEnd) {
        *package = lines.back();
        lines.pop_back();
    }
    for (std::string line : lines) {
        trim(line);
        ParseLine(line);
    }
}

void SamperI2c::ParseLine(std::string line)
{
    std::vector<std::string> oprands;
    std::istringstream f(line);
    std::string s;    
    while (getline(f, s, ' ')) {
        oprands.push_back(s);
    }
    if (oprands.size() != 3 && oprands.size() != 2) {
        return;
    }
    
    ParamAction newAction = {};
    if (oprands[0] == "SET") {
        newAction.cmd = ParamCommand::WRITE_CMD;
        uint16_t index = std::stoul(oprands[1], nullptr, 16);
        newAction.index = index;
        switch (pm->GetType(index)) {
            case ParamType::UINT8: {
                uint8_t value = std::stoul(oprands[2], nullptr, 10);
                *(uint8_t*)(newAction.buf) = value;
            } break;
            case ParamType::INT32: {
                int32_t value = std::stol(oprands[2], nullptr, 10);
                *(int32_t*)(newAction.buf) = value;
            } break;
            default:
                return;
        }
    } else if (oprands[0] == "GET") {
        newAction.cmd = ParamCommand::READ_CMD;
        uint16_t index = std::stoul(oprands[1], nullptr, 16);
        newAction.index = index;
    } else {
        // TODO
        return;
    }
    xQueueSend(normal2realtimeQueue, &newAction, portMAX_DELAY);
}

std::string SamperI2c::BuildString(ParamAction* action)
{
    std::string result;

    std::stringstream ss;
    ss << std::hex << action->index;
    std::string indexStr = ss.str();

    result += indexStr;
    result += " ";

    switch (pm->GetType(action->index)) {
    case ParamType::UINT8:
        result += std::to_string(*(uint8_t*)action->buf);
        break;
    case ParamType::INT32:
        result += std::to_string(*(int32_t*)action->buf);
        break;
    default:
        break;
    }
    result += ";";

    return result;
}
