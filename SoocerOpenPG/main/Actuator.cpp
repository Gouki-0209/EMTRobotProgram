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
        digitalWrite(pin.InAB, HIGH);
    }
    else
    {
        digitalWrite(pin.InAB, LOW);
    }
    ledcWrite(pin.Channel, constrain(abs(speed), 0, 255));
}

void Kicker::set_pin_mode(uint8_t signal_pin)
{
    pinMode(Sig_Pin = signal_pin, OUTPUT);
}
void Kicker::output()
{
    digitalWrite(Sig_Pin, HIGH);
    delay(10);
    digitalWrite(Sig_Pin, LOW);
}
