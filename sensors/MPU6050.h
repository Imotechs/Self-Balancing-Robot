#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>

struct IMUData
{
    float gyroX;
    float accelX;
    float accelY;
    float accelZ;
};

class MPU6050
{
public:

    bool begin();

    bool read(IMUData &data);

    bool calibrateGyro();

    float getGyroOffset() const;

private:

    void writeRegister(uint8_t reg, uint8_t value);

    float gyroXOffset = 0.0;
};

#endif