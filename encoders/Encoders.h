#ifndef ENCODERS_H
#define ENCODERS_H

#include <Arduino.h>

class Encoders
{
public:

    void begin();

    long getLeftCount();

    long getRightCount();

    void reset();

    void updateVelocity(float dt);

    float getVelocity() const;


private:

    long lastLeftCount = 0;
    long lastRightCount = 0;

    float currentVelocity = 0.0;
};

#endif