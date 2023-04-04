#include "motor.h"
#include "pin_definitions.h"

#define PWMA_CHANNEL 0
#define PWMB_CHANNEL 1

void Motor::Create(ParamManager* pm)
{
    this->pm = pm;

    enable = 0;
    velocity = 0;
    forwardComp = 0;
    leftComp = 0;
    rightComp = 0;
    backComp = 0;

    pm->Bind_u8(0x100, &enable);
    pm->Bind_u8(0x110, &velocity);
    pm->Bind_u8(0x120, &forwardComp);
    pm->Bind_u8(0x121, &leftComp);
    pm->Bind_u8(0x122, &rightComp);
    pm->Bind_u8(0x123, &backComp);
}

void Motor::Init()
{
    ledcSetup(PWMA_CHANNEL, 12000, 8);
    ledcSetup(PWMB_CHANNEL, 12000, 8);
    ledcAttachPin(PIN_MOTOR_PWMA, PWMA_CHANNEL);
    ledcAttachPin(PIN_MOTOR_PWMB, PWMB_CHANNEL);

    pinMode(PIN_MOTOR_STBY, OUTPUT);
    pinMode(PIN_MOTOR_AIN1, OUTPUT);
    pinMode(PIN_MOTOR_AIN2, OUTPUT);
    pinMode(PIN_MOTOR_BIN1, OUTPUT);
    pinMode(PIN_MOTOR_BIN2, OUTPUT);
    pinMode(PIN_MOTOR_E1A, INPUT);
    pinMode(PIN_MOTOR_E1B, INPUT);
    pinMode(PIN_MOTOR_E2A, INPUT);
    pinMode(PIN_MOTOR_E2B, INPUT);

    Reset();
}

void Motor::Reset()
{
    enable = 0;
    velocity = 0;
    forwardComp = 0;
    leftComp = 0;
    rightComp = 0;
    backComp = 0;

    digitalWrite(PIN_MOTOR_STBY, LOW);
    digitalWrite(PIN_MOTOR_AIN1, LOW);
    digitalWrite(PIN_MOTOR_AIN2, LOW);
    digitalWrite(PIN_MOTOR_BIN1, LOW);
    digitalWrite(PIN_MOTOR_BIN2, LOW);
    ledcWrite(PWMA_CHANNEL, 0);
    ledcWrite(PWMB_CHANNEL, 0);
}

void Motor::RealtimeCyclic()
{
    int32_t leftMotorSpeed = (int32_t)forwardComp - (int32_t)backComp + (int32_t)rightComp - (int32_t)leftComp;
    int32_t rightMotorSpeed = (int32_t)forwardComp - (int32_t)backComp - (int32_t)rightComp + (int32_t)leftComp;

    if (leftMotorSpeed > 100) {
        int32_t temp = leftMotorSpeed - 100;
        leftMotorSpeed = 100;
        rightMotorSpeed -= temp;
    }
    if (leftMotorSpeed < -100) {
        int32_t temp = -100 - leftMotorSpeed;
        leftMotorSpeed = -100;
        rightMotorSpeed += temp;
    }
    if (rightMotorSpeed > 100) {
        int32_t temp = rightMotorSpeed - 100;
        rightMotorSpeed = 100;
        leftMotorSpeed -= temp;
    }
    if (rightMotorSpeed < -100) {
        int32_t temp = -100 - rightMotorSpeed;
        rightMotorSpeed = -100;
        leftMotorSpeed += temp;
    }

    if (enable) {
        digitalWrite(PIN_MOTOR_STBY, HIGH);
    } else {
        digitalWrite(PIN_MOTOR_STBY, LOW);
        return;
    }

    if (leftMotorSpeed > 0) {
        digitalWrite(PIN_MOTOR_BIN1, LOW);
        digitalWrite(PIN_MOTOR_BIN2, HIGH);
    } else if (leftMotorSpeed < 0) {
        digitalWrite(PIN_MOTOR_BIN1, HIGH);
        digitalWrite(PIN_MOTOR_BIN2, LOW);
    } else {
        digitalWrite(PIN_MOTOR_BIN1, LOW);
        digitalWrite(PIN_MOTOR_BIN2, LOW);
    }

    if (rightMotorSpeed > 0) {
        digitalWrite(PIN_MOTOR_AIN1, LOW);
        digitalWrite(PIN_MOTOR_AIN2, HIGH);
    } else if (rightMotorSpeed < 0) {
        digitalWrite(PIN_MOTOR_AIN1, HIGH);
        digitalWrite(PIN_MOTOR_AIN2, LOW);
    } else {
        digitalWrite(PIN_MOTOR_AIN1, LOW);
        digitalWrite(PIN_MOTOR_AIN2, LOW);
    }

    uint32_t leftMotorPwm = abs(leftMotorSpeed) * 255 / 100;
    uint32_t rightMotorPwm = abs(rightMotorSpeed) * 255 / 100;
    ledcWrite(PWMB_CHANNEL, leftMotorPwm);
    ledcWrite(PWMA_CHANNEL, rightMotorPwm);
}

void Motor::NormalCyclic()
{

}
