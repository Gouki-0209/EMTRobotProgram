#include "ShareObject.h"
ShiftRegister::ShiftRegister(uint8_t PIN_SER, uint8_t PIN_SRCLK, uint8_t PIN_RCLK)
{
    pinMode(SER = PIN_SER, OUTPUT);
    pinMode(SRCLK = PIN_SRCLK, OUTPUT);
    pinMode(RCLK = PIN_RCLK, OUTPUT);
}
void ShiftRegister::Send_Byte(byte pin_addr, byte pin_mode)
{
    if (pin_mode == 0x01)
    {
        send_addr |= pin_addr;
    }
    else if (pin_mode == 0x02)
    {
        send_addr &= ~pin_addr;
    }

    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, MSBFIRST, send_addr);
    digitalWrite(RCLK, HIGH);
}
def_func::def_func()
{
    TH_ABS = 255;
}
def_func::def_func(int set_th_abs)
{
    TH_ABS = set_th_abs;
}
float def_func::LPF(float Data, float a)
{
    float Y;
    Y = a * PreY + (1.0 - a) * Data;
    PreY = Y;
    return Y;
}
int def_func::PID(double Data, double target)
{
    //  Serial.println(Data);
    dt = (micros() - preTime) * 1e-6;
    preTime = micros();
    P = Data - target;
    I += P * dt;
    D = (P - preP) / dt;
    preP = P;
    duty = Kp * P + Ki * I + Kd * D;
    return (constrain(duty, -TH_ABS, TH_ABS));
}
