#include "MotorController.h"
#include "../config.h"


void MotorController::begin()
{
    pinMode(STBY_PIN, OUTPUT);

    pinMode(AIN1_PIN, OUTPUT);
    pinMode(AIN2_PIN, OUTPUT);

    pinMode(BIN1_PIN, OUTPUT);
    pinMode(BIN2_PIN, OUTPUT);


    digitalWrite(STBY_PIN, HIGH);


    ledcAttach(
        PWMA_PIN,
        PWM_FREQ,
        PWM_RESOLUTION
    );

    ledcAttach(
        PWMB_PIN,
        PWM_FREQ,
        PWM_RESOLUTION
    );


    ledcWrite(PWMA_PIN, 0);
    ledcWrite(PWMB_PIN, 0);
}


void MotorController::driveMotorA(int speed)
{
    speed = constrain(speed, -255, 255);


    if (speed > 0)
    {
        digitalWrite(AIN1_PIN, HIGH);
        digitalWrite(AIN2_PIN, LOW);
    }
    else if (speed < 0)
    {
        digitalWrite(AIN1_PIN, LOW);
        digitalWrite(AIN2_PIN, HIGH);
    }
    else
    {
        digitalWrite(AIN1_PIN, LOW);
        digitalWrite(AIN2_PIN, LOW);
    }


    ledcWrite(PWMA_PIN, abs(speed));
}


void MotorController::driveMotorB(int speed)
{
    speed = constrain(speed, -255, 255);


    if (speed > 0)
    {
        digitalWrite(BIN1_PIN, HIGH);
        digitalWrite(BIN2_PIN, LOW);
    }
    else if (speed < 0)
    {
        digitalWrite(BIN1_PIN, LOW);
        digitalWrite(BIN2_PIN, HIGH);
    }
    else
    {
        digitalWrite(BIN1_PIN, LOW);
        digitalWrite(BIN2_PIN, LOW);
    }


    ledcWrite(PWMB_PIN, abs(speed));
}


void MotorController::drive(float power)
{
    int pwm = (int)power;

    driveMotorA(pwm);

    // Motor B is physically mounted opposite
    driveMotorB(-pwm);
}


void MotorController::stop()
{
    drive(0);
}