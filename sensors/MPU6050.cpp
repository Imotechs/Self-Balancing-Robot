#include "MPU6050.h"
#include "../config.h"

#include <Wire.h>
#include <math.h>


bool MPU6050::begin()
{
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(400000);

    delay(100);

    // Wake MPU6050
    writeRegister(0x6B, 0x00);
    delay(100);

    // Accelerometer ±2g
    writeRegister(0x1C, 0x00);
    delay(100);

    // Gyroscope ±250°/s
    writeRegister(0x1B, 0x00);
    delay(100);

    // DLPF configuration
    writeRegister(0x1A, 0x01);
    delay(100);

    return true;
}


void MPU6050::writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(MPU_ADDR);

    Wire.write(reg);
    Wire.write(value);

    Wire.endTransmission();
}


bool MPU6050::read(IMUData &data)
{
    Wire.beginTransmission(MPU_ADDR);

    Wire.write(0x3B);

    if (Wire.endTransmission(false) != 0)
    {
        return false;
    }

    if (Wire.requestFrom(MPU_ADDR, 14) != 14)
    {
        return false;
    }

    int16_t rawAccelX =
        (Wire.read() << 8) | Wire.read();

    int16_t rawAccelY =
        (Wire.read() << 8) | Wire.read();

    int16_t rawAccelZ =
        (Wire.read() << 8) | Wire.read();


    // Skip temperature
    Wire.read();
    Wire.read();


    int16_t rawGyroX =
        (Wire.read() << 8) | Wire.read();


    // Skip Gyro Y and Z
    Wire.read();
    Wire.read();
    Wire.read();
    Wire.read();


    data.accelX = rawAccelX / 16384.0;
    data.accelY = rawAccelY / 16384.0;
    data.accelZ = rawAccelZ / 16384.0;

    data.gyroX =
        (rawGyroX / 131.0) - gyroXOffset;


    return true;
}


bool MPU6050::calibrateGyro()
{
    Serial.println();
    Serial.println("================================");
    Serial.println("      GYRO CALIBRATION");
    Serial.println("================================");
    Serial.println();

    Serial.println("Keep the robot COMPLETELY STILL.");
    Serial.println("Calibration starts in 3 seconds...");

    delay(3000);


    const int samples = 1000;

    float sum = 0.0;
    int validSamples = 0;


    Serial.println("Calibrating...");


    for (int i = 0; i < samples; i++)
    {
        IMUData data;

        if (read(data))
        {
            // read() already subtracts the current offset,
            // so temporarily calculate the raw gyro value
            // from the sensor again is undesirable.
            //
            // Therefore this implementation assumes the
            // initial offset is zero.
            sum += data.gyroX;
            validSamples++;
        }

        delay(2);
    }


    if (validSamples == 0)
    {
        Serial.println("ERROR: MPU6050 NOT RESPONDING!");

        return false;
    }


    gyroXOffset = sum / validSamples;


    Serial.println();
    Serial.println("Calibration complete.");

    Serial.print("Gyro X offset: ");
    Serial.print(gyroXOffset, 3);
    Serial.println(" °/s");

    Serial.println();


    return true;
}


float MPU6050::getGyroOffset() const
{
    return gyroXOffset;
}