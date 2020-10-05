#include "ShareParts.h"

int ShareObject::LPF(int Value, float a){
  int Y;
  Y = a * PreY + (1 - a) * Value;
  PreY = Y;
  return Y; 
}
int ShareObject::PID(double value,double target){
  dt = (micros() - preTime) * 1e-6;
  preTime = micros();
  P = value - target;
  I += P * dt; 
  D = (P - preP) / dt;
  preP = P;
  duty = Kp * P + Ki * I + Kd * D;
  return(constrain(duty, -127, 127));
}
