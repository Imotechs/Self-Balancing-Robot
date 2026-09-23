#include <Arduino.h>

#include "config.h"

#include "sensors/MPU6050.h"
#include "motors/MotorController.h"
#include "encoders/Encoders.h"

#include "control/ComplementaryFilter.h"
#include "control/AnglePID.h"
#include "control/VelocityController.h"


// OBJECTS

MPU6050 imu;

MotorController motors;

Encoders encoders;

ComplementaryFilter angleFilter;

AnglePID anglePID;

VelocityController velocityController;


// ROBOT STATE

float currentAngle = 0.0;

float accelAngle = 0.0;

float gyroRate = 0.0;

float targetAngle = 0.0;

float targetVelocity = 0.0;

float currentVelocity = 0.0;

float motorPower = 0.0;



// TIMING

unsigned long previousTime = 0;

unsigned long lastVelocityUpdateTime = 0;


// SETUP

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);

    delay(500);


    // MPU6050

    imu.begin();

    imu.calibrateGyro();


    // Get initial angle

    IMUData data;

    if (imu.read(data))
    {
        accelAngle =
            atan2(
                data.accelY,
                data.accelZ
            )
            *
            180.0
            /
            PI;


        currentAngle = accelAngle;

        angleFilter.begin(currentAngle);
    }


    // Motors

    motors.begin();


    // Encoders

    encoders.begin();

    encoders.reset();


    // Controllers

    anglePID.begin();

    velocityController.begin();


    // Timing

    previousTime = micros();

    lastVelocityUpdateTime = millis();


    Serial.println("================================");
    Serial.println("  SELF BALANCING ROBOT");
    Serial.println("================================");
    Serial.println();

    Serial.println("Motors ARE connected to control now.");
}


// MAIN LOOP

void loop()
{
    unsigned long currentTime =
        micros();


    float dt =
        (currentTime - previousTime)
        /
        1000000.0;


    previousTime = currentTime;


    if (dt <= 0.0 || dt > 0.1)
    {
        return;
    }


    // READ IMU

    IMUData data;


    if (!imu.read(data))
    {
        Serial.println(
            "MPU6050 read error!"
        );

        motors.stop();

        delay(100);

        return;
    }


    gyroRate =
        data.gyroX -
        imu.getGyroOffset();


    accelAngle =
        atan2(
            data.accelY,
            data.accelZ
        )
        *
        180.0
        /
        PI;


    // COMPLEMENTARY FILTER

    currentAngle =
        angleFilter.update(
            gyroRate,
            accelAngle,
            dt
        );


    // SAFETY CUTOFF

    if (abs(currentAngle) >
        FALL_ANGLE_LIMIT)
    {
        motors.stop();

        anglePID.reset();

        velocityController.reset();

        targetAngle = 0.0;

        Serial.println(
            "FALLEN - motors stopped"
        );

        delay(100);

        return;
    }


    // VELOCITY OUTER LOOP

    unsigned long nowMs =
        millis();


    if (
        nowMs -
        lastVelocityUpdateTime
        >= VELOCITY_UPDATE_INTERVAL_MS
    )
    {
        float velocityDt =
            (
                nowMs -
                lastVelocityUpdateTime
            )
            /
            1000.0;


        lastVelocityUpdateTime =
            nowMs;


        encoders.updateVelocity(
            velocityDt
        );


        currentVelocity =
            encoders.getVelocity();


        targetAngle =
            velocityController.update(
                targetVelocity,
                currentVelocity,
                currentAngle,
                velocityDt
            );
    }


    // ANGLE INNER LOOP

    motorPower =
        anglePID.update(
            targetAngle,
            currentAngle,
            dt
        );


    // MOTOR OUTPUT

    motors.drive(
        motorPower
    );


    // DEBUG OUTPUT

    Serial.print("Filtered: ");

    Serial.print(
        currentAngle,
        2
    );


    Serial.print(
        "° | TargetAngle: "
    );

    Serial.print(
        targetAngle,
        2
    );


    Serial.print(
        " | Vel: "
    );

    Serial.print(
        currentVelocity,
        1
    );


    Serial.print(
        " | Motor: "
    );

    Serial.print(
        motorPower,
        2
    );


    Serial.println();


    delay(5);
}