#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

class MotorController
{
public:

    void begin();

    void driveMotorA(int speed);

    void driveMotorB(int speed);

    void drive(float power);

    void stop();

};

#endif