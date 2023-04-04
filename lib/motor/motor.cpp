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

}

void Motor::NormalCyclic()
{

}


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