#include "HCSR04.h"

void HCSR04Sensor::setSensorPins(){
  for(int i=0;i < HCSR04_NUM;i++){
    pinMode(SensorTrig[i],OUTPUT);
  }
  for(int i=0;i < HCSR04_NUM;i++){
    pinMode(SensorEcho[i],INPUT);
  }
}

void HCSR04Sensor::getSensorDistance(float Duration[]){
  for(int i=0;i < HCSR04_NUM;i++){
    digitalWrite(SensorTrig[i], LOW);
    delayMicroseconds(2);
    digitalWrite(SensorTrig[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(SensorTrig[i], LOW);
    Duration[i] = pulseIn(SensorEcho[i], HIGH);
  } 
}
