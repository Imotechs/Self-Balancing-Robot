#include "ComplementaryFilter.h"
#include "../config.h"


void ComplementaryFilter::begin(float initialAngle)
{
    angle = initialAngle;
}


float ComplementaryFilter::update(
    float gyroRate,
    float accelAngle,
    float dt
)
{
    float alpha =
        FILTER_TAU /
        (FILTER_TAU + dt);


    angle =
        alpha *
        (angle + gyroRate * dt)
        +
        (1.0 - alpha) *
        accelAngle;


    return angle;
}


float ComplementaryFilter::getAngle() const
{
    return angle;
}