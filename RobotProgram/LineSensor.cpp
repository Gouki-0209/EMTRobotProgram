#include "LineSensor.h"

void LineSensor::Judgement(byte LineValue){
  if(LineValue == B0001){
    flag = false;
    preAngle = 90;
    startTime = millis();
  }
  if(LineValue == B0010){
    flag = false;
    preAngle = 180;
    startTime = millis();
  }
  if(LineValue == B0100){
    flag = false;
    preAngle = -90;
    startTime = millis();
  }
  if(LineValue == B0001 && LineValue == B0010){
    flag = false;
    preAngle = 135;
    startTime = millis();
  }
  if(LineValue == B0010 && LineValue == B0100){
    flag = false;
    preAngle = -135;
    startTime = millis();
  }
}
int LineSensor::upload(byte LineValue, int IRAngle){
  Judgement(LineValue);
  if((millis() - startTime) > 130){
    flag = true;
  }
  if(flag == false){
    return preAngle;
  } else {
    return IRAngle;
  }
}
