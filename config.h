#ifndef CONFIG_H
#define CONFIG_H

// =====================================================
// MPU6050
// =====================================================

#define MPU_ADDR 0x68

#define SDA_PIN 18
#define SCL_PIN 19


// =====================================================
// TB6612FNG MOTOR DRIVER
// =====================================================

#define STBY_PIN 13

#define AIN1_PIN 21
#define AIN2_PIN 17
#define PWMA_PIN 25

#define BIN1_PIN 27
#define BIN2_PIN 14
#define PWMB_PIN 26

#define PWM_FREQ 5000
#define PWM_RESOLUTION 8


// =====================================================
// ENCODERS
// =====================================================

#define ENC_LEFT_A_PIN  34
#define ENC_LEFT_B_PIN  35

#define ENC_RIGHT_A_PIN 32
#define ENC_RIGHT_B_PIN 33


// Encoder direction correction
#define ENC_LEFT_SIGN  1
#define ENC_RIGHT_SIGN 1


// =====================================================
// COMPLEMENTARY FILTER
// =====================================================

#define FILTER_TAU 0.75


// =====================================================
// ANGLE PID
// =====================================================

#define ANGLE_KP 19.0
#define ANGLE_KI 0.1
#define ANGLE_KD 0.8

#define ERROR_SUM_LIMIT 300.0
#define MOTOR_POWER_LIMIT 255.0


// =====================================================
// VELOCITY CONTROLLER
// =====================================================

#define VELOCITY_KP 0.015
#define VELOCITY_KI 0.005

#define VELOCITY_ERROR_SUM_LIMIT 2000.0

#define MAX_ANGLE_BIAS 3.0

#define VELOCITY_LOOP_ANGLE_GATE 8.0

#define VELOCITY_UPDATE_INTERVAL_MS 20


// =====================================================
// SAFETY
// =====================================================

#define FALL_ANGLE_LIMIT 45.0


// =====================================================
// SERIAL
// =====================================================

#define SERIAL_BAUDRATE 115200

#endif