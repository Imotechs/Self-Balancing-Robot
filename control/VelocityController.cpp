#include "VelocityController.h"
#include "../config.h"

#include <Arduino.h>


void VelocityController::begin()
{
    reset();
}


float VelocityController::update(
    float targetVelocity,
    float currentVelocity,
    float currentAngle,
    float dt
)
{
    if (dt <= 0.0)
        return 0.0;


    // Do not interfere with aggressive
    // tilt recovery.
    if (abs(currentAngle) >
        VELOCITY_LOOP_ANGLE_GATE)
    {
        reset();

        return 0.0;
    }


    float error =
        targetVelocity - currentVelocity;


    velocityErrorSum +=
        error * dt;


    velocityErrorSum =
        constrain(
            velocityErrorSum,
            -VELOCITY_ERROR_SUM_LIMIT,
            VELOCITY_ERROR_SUM_LIMIT
        );


    float angleBias =
        VELOCITY_KP * error
        +
        VELOCITY_KI * velocityErrorSum;


    angleBias =
        constrain(
            angleBias,
            -MAX_ANGLE_BIAS,
            MAX_ANGLE_BIAS
        );


    return angleBias;
}


void VelocityController::reset()
{
    velocityErrorSum = 0.0;
}