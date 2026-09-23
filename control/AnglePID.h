#ifndef ANGLE_PID_H
#define ANGLE_PID_H

class AnglePID
{
public:

    void begin();

    float update(
        float targetAngle,
        float currentAngle,
        float dt
    );

    void reset();

private:

    float previousError = 0.0;
    float errorSum = 0.0;
};

#endif