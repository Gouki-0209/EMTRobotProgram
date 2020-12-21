#ifndef __ShareObject__
#define __ShareObject_

//  74HC252D用の定義
#define MOTOR_1 0b10000000
#define MOTOR_2 0b01000000
#define MOTOR_3 0b00100000
#define SOLENOID 0b00010000
#define DRIBBLER 0b00001000
#define CS_1 0b00000100
#define CS_2 0b00000010
#define CS_3 0b00000001

#define PIN_HIGH
#define PIN_LOW

class _74HC252D_
{
private:
    uint8_t SER, SRLCK, RCLK;
    byte send_addr;

public:
    _74HC252D_(uint8_t PIN_SER, uint8_t PIN_SRCLK, uint8_t PIN_RCLK);
    void Send_Byte(byte pin_addr, byte pin_mode);
}

#endif