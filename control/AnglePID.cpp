#include "AnglePID.h"
#include "../config.h"

#include <Arduino.h>


void AnglePID::begin()
{
    reset();
}


float AnglePID::update(
    float targetAngle,
    float currentAngle,
    float dt
)
{
    if (dt <= 0.0)
        return 0.0;


    float error =
        targetAngle - currentAngle;


    errorSum += error;

    errorSum =
        constrain(
            errorSum,
            -ERROR_SUM_LIMIT,
            ERROR_SUM_LIMIT
        );


    float angleRate =
        (currentAngle - previousError) / dt;


    float P =
        ANGLE_KP * error;


    float I =
        ANGLE_KI * errorSum * dt;


    float D =
        -ANGLE_KD * angleRate;


    previousError = currentAngle;


    float output =
        P + I + D;


    return constrain(
        output,
        -MOTOR_POWER_LIMIT,
        MOTOR_POWER_LIMIT
    );
}


void AnglePID::reset()
{
    previousError = 0.0;
    errorSum = 0.0;
}