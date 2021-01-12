#include "Actuator.h"
void set_Motor_channel(uint8_t PIN_count){
  for(int i = 0;i < PIN_count; i++){
    ledcSetup(i,490,8);
  }
}
void set_Motor_pin(MotorPins &pin, uint8_t inAB, uint8_t pwm, uint8_t channel)
{
    pinMode(pin.InAB = inAB, OUTPUT);
    ledcAttachPin(pwm, pin.Channel=channel);
}
void Motor_spin(MotorPins &pin, int speed)
{
    if (speed <= 0)
    {
        digitalWrite(pin.InAB, LOW);
    }
    else
    {
        digitalWrite(pin.InAB, HIGH);
    }
    ledcWrite(pin.Channel, constrain(abs(speed), 0, 255));
}

void set_Kicker_pin(uint8_t signal_pin)
{
    pinMode(signal_pin, OUTPUT);
}
void Kick(uint8_t signal_pin)
{
    digitalWrite(signal_pin, HIGH);
    delay(10);
    digitalWrite(signal_pin, LOW);
}
