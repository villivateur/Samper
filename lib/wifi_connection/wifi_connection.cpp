#include "wifi_connection.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <sstream>
#include <vector>
#include "string_utils.h"


IPAddress localIp(192, 168, 2, 50);
IPAddress gatewayIp(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDns(223, 5, 5, 5);
IPAddress secondaryDns(8, 8, 4, 4);
WiFiUDP udp;


void WifiConnection::Create(ParamManager* pm)
{
    this->pm = pm;

    enable = 1;
    udpListening = 0;

    pm->Bind_u8(0x10, &enable);
}

void WifiConnection::Init()
{
    if (!enable) {
        return;
    }

    WiFi.config(localIp, gatewayIp, subnet, primaryDns, secondaryDns);
    WiFi.begin("VVAILL", "channy161021");

    uint32_t timeout = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        timeout += 50;
        if (timeout > 15000) {
            return;
        }
    }

    Reset();
}

void WifiConnection::Reset()
{
    connected = 0;
}

void WifiConnection::RealtimeCyclic()
{
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }

    ParamAction reqeust = {};
    while (xQueueReceive(pm->paramDownloadQueue, &reqeust, 0)) {
        switch (reqeust.cmd) {
            case ParamCommand::WRITE_CMD: {
                switch (pm->GetType(reqeust.index)) {
                    case ParamType::UINT8: {
                        pm->Set_u8(reqeust.index, *(uint8_t*)(reqeust.buf));
                    } break;
                    case ParamType::INT32: {
                        pm->Set_i32(reqeust.index, *(int32_t*)(reqeust.buf));
                    } break;
                    case ParamType::UINT32: {
                        pm->Set_u32(reqeust.index, *(uint32_t*)(reqeust.buf));
                    } break;
                    default:
                        break;
                }
                ParamAction response;
                response.cmd = ParamCommand::WRITE_RESP;
                response.index = reqeust.index;
                xQueueSend(pm->paramUploadQueue, &response, 0);
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
                    case ParamType::UINT32: {
                        *(uint32_t*)response.buf = pm->Get_u32(reqeust.index);
                    } break;
                    default:
                        break;
                }
                xQueueSend(pm->paramUploadQueue, &response, 0);
            } break;
            default:
                break;
        }
    }
}

void WifiConnection::NormalCyclic()
{
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }
    if (!udpListening) {
        udp.begin(UDP_PORT);
        udpListening = 1;
    }

    ParamAction response;

    if (connected) {
        while (xQueueReceive(pm->paramUploadQueue, &response, 0)) {
            udp.beginPacket(udp.remoteIP(), udp.remotePort());
            udp.println(BuildString(&response).c_str());
            udp.endPacket();
        }
    }

    char tmpPack[UDP_MAX_PACKAGE_SIZE] = {0};
    int packetSize = udp.parsePacket();
    if (packetSize > 0 && packetSize <= UDP_MAX_PACKAGE_SIZE) {
        int len = udp.read(tmpPack, UDP_MAX_PACKAGE_SIZE);
        connected = 1;
        ParsePackage(tmpPack, len);
    }
}

void WifiConnection::ParsePackage(char* package, int len)
{
    std::string rawStr = package;
    std::vector<std::string> lines;
    std::istringstream f(rawStr);
    std::string s;    
    while (getline(f, s, ';')) {
        lines.push_back(s);
    }
    for (std::string line : lines) {
        trim(line);
        ParseLine(line);
    }
}

void WifiConnection::ParseLine(std::string line)
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
            case ParamType::UINT32: {
                uint32_t value = std::stoul(oprands[2], nullptr, 10);
                *(uint32_t*)(newAction.buf) = value;
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
    xQueueSend(pm->paramDownloadQueue, &newAction, portMAX_DELAY);
}

std::string WifiConnection::BuildString(ParamAction* action)
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
    case ParamType::UINT32:
        result += std::to_string(*(uint32_t*)action->buf);
        break;
    default:
        break;
    }
    result += ";";

    return result;
}
