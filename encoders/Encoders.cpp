#include "Encoders.h"
#include "../config.h"


volatile long encoderCountLeft = 0;
volatile long encoderCountRight = 0;


void IRAM_ATTR isrEncoderLeft()
{
    bool b = digitalRead(ENC_LEFT_B_PIN);

    if (b)
        encoderCountLeft++;
    else
        encoderCountLeft--;
}


void IRAM_ATTR isrEncoderRight()
{
    bool b = digitalRead(ENC_RIGHT_B_PIN);

    if (b)
        encoderCountRight++;
    else
        encoderCountRight--;
}


void Encoders::begin()
{
    pinMode(ENC_LEFT_A_PIN, INPUT);
    pinMode(ENC_LEFT_B_PIN, INPUT);

    pinMode(ENC_RIGHT_A_PIN, INPUT);
    pinMode(ENC_RIGHT_B_PIN, INPUT);


    attachInterrupt(
        digitalPinToInterrupt(ENC_LEFT_A_PIN),
        isrEncoderLeft,
        RISING
    );

    attachInterrupt(
        digitalPinToInterrupt(ENC_RIGHT_A_PIN),
        isrEncoderRight,
        RISING
    );
}


long Encoders::getLeftCount()
{
    noInterrupts();

    long count = encoderCountLeft;

    interrupts();

    return count;
}


long Encoders::getRightCount()
{
    noInterrupts();

    long count = encoderCountRight;

    interrupts();

    return count;
}


void Encoders::reset()
{
    noInterrupts();

    encoderCountLeft = 0;
    encoderCountRight = 0;

    interrupts();

    lastLeftCount = 0;
    lastRightCount = 0;

    currentVelocity = 0.0;
}


void Encoders::updateVelocity(float dt)
{
    if (dt <= 0.0)
        return;


    long leftCount = getLeftCount();
    long rightCount = getRightCount();


    long deltaLeft =
        leftCount - lastLeftCount;

    long deltaRight =
        rightCount - lastRightCount;


    lastLeftCount = leftCount;
    lastRightCount = rightCount;


    float leftVelocity =
        (ENC_LEFT_SIGN * deltaLeft) / dt;

    float rightVelocity =
        (ENC_RIGHT_SIGN * deltaRight) / dt;


    currentVelocity =
        (leftVelocity + rightVelocity) / 2.0;
}


float Encoders::getVelocity() const
{
    return currentVelocity;
}