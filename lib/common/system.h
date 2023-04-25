#pragma once

#define NORMAL_CYCLE_MS 5
#define REALTIME_CYCLE_MS 2

#define WAIT_RUN_PERIOD_NORMAL_CYCLE(t) do { \
        static uint32_t idleTime = 0; \
        idleTime += NORMAL_CYCLE_MS; \
        if (idleTime <= t) { \
            return; \
        } \
        idleTime = 0;\
    } while (0)

#define WAIT_RUN_PERIOD_REALTIME_CYCLE(t) do { \
        static uint32_t idleTime = 0; \
        idleTime += REALTIME_CYCLE_MS; \
        if (idleTime <= t) { \
            return; \
        } \
        idleTime = 0;\
    } while (0)
