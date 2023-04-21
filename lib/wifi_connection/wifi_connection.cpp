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
}

void WifiConnection::Reset()
{

}

void WifiConnection::RealtimeCyclic()
{
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }

    ParamAction newAction = {};
    while (xQueueReceive(pm->paramDownloadQueue, &newAction, 0)) {
        switch (newAction.cmd) {
            case ParamCommand::WRITE_CMD: {
                switch (pm->GetType(newAction.index))
                {
                    case ParamType::UINT8: {
                        pm->Set_u8(newAction.index, *(uint8_t*)(newAction.buf));
                    } break;
                    case ParamType::INT32: {
                        pm->Set_i32(newAction.index, *(int32_t*)(newAction.buf));
                    } break;
                    case ParamType::UINT32: {
                        pm->Set_u32(newAction.index, *(uint32_t*)(newAction.buf));
                    } break;
                    default:
                        return;
                }
            } break;
            case ParamCommand::READ_CMD: {
                // TODO
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

    char tmpPack[UDP_MAX_PACKAGE_SIZE] = {0}; 
    int packetSize = udp.parsePacket();
    if (packetSize > 0 && packetSize <= UDP_MAX_PACKAGE_SIZE) {
        int len = udp.read(tmpPack, UDP_MAX_PACKAGE_SIZE);
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
    if (oprands.size() != 3) {
        return;
    }
    
    ParamAction newAction = {};
    if (oprands[0] == "SET") {
        newAction.cmd = ParamCommand::WRITE_CMD;
        uint16_t index = std::stoul(oprands[1], nullptr, 16);
        newAction.index = index;
        switch (pm->GetType(index))
        {
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
        // TODO
        return;
    } else {
        // TODO
        return;
    }
    xQueueSend(pm->paramDownloadQueue, &newAction, portMAX_DELAY);
}
