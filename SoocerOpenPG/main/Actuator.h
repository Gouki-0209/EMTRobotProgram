#ifndef __Actuator__
#define __Actuator__


#include "ShareObject.h"

typedef struct {
  uint8_t InAB;
  uint8_t Channel;
} MotorPins;

void set_Motor_channel(uint8_t PIN_count);
void set_Motor_pin(MotorPins &pin, uint8_t inAB, uint8_t pwm, uint8_t channel);
void Motor_spin(MotorPins &pin, int speed);

class Kicker
{
private:
    uint8_t Sig_Pin;

public:
    void set_pin_mode(uint8_t signal_pin);
    void output();
};

#endif
