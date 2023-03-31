#include <Arduino.h>
#include "pin_definitions.h"
#include "core.h"
#include "motor.h"
#include "status_led.h"
#include "wifi_connection.h"


Core core;
Motor motor;
WifiConnection network;
StatusLed statusLed;

void setup() {
    core.Init();
    core.AddDevice(&motor);
    core.AddDevice(&network);
    core.AddDevice(&statusLed);
    core.InitDevices();
}

void loop() {
    core.NormalCyclic();
    // // forward
    // digitalWrite(MOTOR_AIN1, HIGH);
    // digitalWrite(MOTOR_AIN2, LOW);
    // digitalWrite(MOTOR_BIN1, LOW);
    // digitalWrite(MOTOR_BIN2, HIGH);
    // ledcWrite(PWM_CHANNEL0, 512);
    // ledcWrite(PWM_CHANNEL1, 512);
    // delay(2000);

    // // hold
    // digitalWrite(MOTOR_AIN1, LOW);
    // digitalWrite(MOTOR_AIN2, LOW);
    // digitalWrite(MOTOR_BIN1, LOW);
    // digitalWrite(MOTOR_BIN2, LOW);
    // ledcWrite(PWM_CHANNEL0, 0);
    // ledcWrite(PWM_CHANNEL1, 0);
    // delay(2000);

    // // back
    // digitalWrite(MOTOR_AIN1, LOW);
    // digitalWrite(MOTOR_AIN2, HIGH);
    // digitalWrite(MOTOR_BIN1, HIGH);
    // digitalWrite(MOTOR_BIN2, LOW);
    // ledcWrite(PWM_CHANNEL0, 512);
    // ledcWrite(PWM_CHANNEL1, 512);
    // delay(2000);

    // // hold
    // digitalWrite(MOTOR_AIN1, LOW);
    // digitalWrite(MOTOR_AIN2, LOW);
    // digitalWrite(MOTOR_BIN1, LOW);
    // digitalWrite(MOTOR_BIN2, LOW);
    // ledcWrite(PWM_CHANNEL0, 0);
    // ledcWrite(PWM_CHANNEL1, 0);
    // delay(2000);
}
