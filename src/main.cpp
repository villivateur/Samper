#include <Arduino.h>
#include "motor_pins.h"

void setup() {
    pinMode(INPUT0, INPUT);
    pinMode(INPUT1, INPUT);
    pinMode(INPUT2, INPUT);
    pinMode(INPUT3, INPUT);

    pinMode(OUTPUT0, OUTPUT);
    pinMode(OUTPUT1, OUTPUT);
    pinMode(OUTPUT2, OUTPUT);
    pinMode(OUTPUT3, OUTPUT);
    digitalWrite(OUTPUT0, LOW);
    digitalWrite(OUTPUT1, LOW);
    digitalWrite(OUTPUT2, LOW);
    digitalWrite(OUTPUT3, LOW);

    ledcSetup(PWM_CHANNEL0, 5000, 10);
    ledcSetup(PWM_CHANNEL1, 5000, 10);
    ledcSetup(PWM_CHANNEL2, 5000, 10);
    ledcSetup(PWM_CHANNEL3, 5000, 10);
    ledcAttachPin(PWM0, PWM_CHANNEL0);
    ledcAttachPin(PWM1, PWM_CHANNEL1);
    ledcAttachPin(PWM2, PWM_CHANNEL2);
    ledcAttachPin(PWM3, PWM_CHANNEL3);
    ledcWrite(PWM_CHANNEL0, 0);
    ledcWrite(PWM_CHANNEL1, 0);
    ledcWrite(PWM_CHANNEL2, 0);
    ledcWrite(PWM_CHANNEL3, 0);
}

void loop() {
    // forward
    digitalWrite(MOTOR_AIN1, HIGH);
    digitalWrite(MOTOR_AIN2, LOW);
    digitalWrite(MOTOR_BIN1, LOW);
    digitalWrite(MOTOR_BIN2, HIGH);
    ledcWrite(PWM_CHANNEL0, 512);
    ledcWrite(PWM_CHANNEL1, 512);
    delay(2000);

    // hold
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, LOW);
    digitalWrite(MOTOR_BIN1, LOW);
    digitalWrite(MOTOR_BIN2, LOW);
    ledcWrite(PWM_CHANNEL0, 0);
    ledcWrite(PWM_CHANNEL1, 0);
    delay(2000);

    // back
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, HIGH);
    digitalWrite(MOTOR_BIN1, HIGH);
    digitalWrite(MOTOR_BIN2, LOW);
    ledcWrite(PWM_CHANNEL0, 512);
    ledcWrite(PWM_CHANNEL1, 512);
    delay(2000);

    // hold
    digitalWrite(MOTOR_AIN1, LOW);
    digitalWrite(MOTOR_AIN2, LOW);
    digitalWrite(MOTOR_BIN1, LOW);
    digitalWrite(MOTOR_BIN2, LOW);
    ledcWrite(PWM_CHANNEL0, 0);
    ledcWrite(PWM_CHANNEL1, 0);
    delay(2000);
}
