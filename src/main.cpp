#include <Arduino.h>
#include "system.h"
#include "pin_definitions.h"
#include "core.h"
#include "motor.h"
#include "status_led.h"
#include "wifi_connection.h"
#include "beep.h"


Core core;
Motor motor;
WifiConnection network;
StatusLed statusLed;
Beep beep;

void RealtimeTask(void* p);

void setup()
{
    Serial.begin(115200);
    
    core.Init();
    core.AddDevice(&network);
    core.AddDevice(&motor);
    core.AddDevice(&statusLed);
    core.AddDevice(&beep);
    core.InitDevices();

    xTaskCreate(
        RealtimeTask,
        "Realtime Task",
        16384,
        NULL,
        configMAX_PRIORITIES - 1,
        NULL
    );
}

void loop()
{
    core.NormalCyclic();
    delay(NORMAL_CYCLE_MS);
}

void RealtimeTask(void* p)
{
    // For thread safety
    // You can only change parameters variable in this task

    TickType_t xLastWakeTime;
    const TickType_t xFrequency = REALTIME_CYCLE_MS;

    xLastWakeTime = xTaskGetTickCount();

    while (1) {
        core.RealtimeCyclic();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
