#ifndef __ShareObject__
#define __ShareObject__

#include "Arduino.h"
#include <Wire.h>

//  74HC252D用の定義
#define MOTOR_1 0b10000000
#define MOTOR_2 0b01000000
#define MOTOR_3 0b00100000
#define SOLENOID 0b00010000
#define DRIBBLER 0b00001000
#define CS_1 0b00000100
#define CS_2 0b00000010
#define CS_3 0b00000001

#define PIN_HIGH 0x01
#define PIN_LOW 0x02

#define Kp 1.8
#define Ki 0.01
#define Kd 0.1

class ShiftRegister
{
private:
    uint8_t SER, SRCLK, RCLK;
    byte send_addr;

public:
    ShiftRegister(uint8_t PIN_SER, uint8_t PIN_SRCLK, uint8_t PIN_RCLK);
    void Send_Byte(byte pin_addr, byte pin_mode);
};

class def_func
{
private:
    int PreY = 0;
    double duty = 0;
    double dt, preTime;
    double P, I = 0, D, preP = 0;
    int TH_ABS;

public:
    def_func();
    def_func(int set_th_abs);
    float LPF(float Data, float a);
    int PID(double Data, double target);
};

#endif
