#include "ShareObject.h"
_74HC252D_::_74HC252D_(uint8_t PIN_SER, uint8_t PIN_SRCLK, uint8_t PIN_RCLK)
{
    pinMode(SER = PIN_SER, OUTPUT);
    pinMode(SRCLK = PIN_SRCLK, OUTPUT);
    pinMode(RCLK = PIN_RCLK, OUTPUT);
}
void _74HC252D_::Send_Byte(byte pin_addr, byte pin_mode)
{
    if (pin_mode == PIN_HIGH)
    {
        send_addr |= pin_addr
    }
    else if (pin_mode == PIN_LOW)
    {
        send_addr &= ~pin_addr
    }

    digitalWrite(RCLK LOW);
    shiftOut(SER, SRCLK, MSBFIRST, send_addr);
    digitalWrite(RCLK, HIGH);
}
