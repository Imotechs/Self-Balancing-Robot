#ifndef VELOCITY_CONTROLLER_H
#define VELOCITY_CONTROLLER_H

class VelocityController
{
public:

    void begin();

    float update(
        float targetVelocity,
        float currentVelocity,
        float currentAngle,
        float dt
    );

    void reset();

private:

    float velocityErrorSum = 0.0;
};

#endif