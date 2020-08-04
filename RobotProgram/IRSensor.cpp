#include "IRSensor.h"

void IRSensor::setSensorPins(){
  for(int i=0;i < IR_NUM;i++){
    pinMode(SensorPins[i], INPUT);
  }
}

void IRSensor::getSensorPulseWidth(float pulseWidth[]){
  pulseWidth[IR_NUM] = {};
  for (int i=0;i < IR_NUM;i++){
    pulseWidth[i] = pulseIn(SensorPins[i], HIGH);
  }
}

Vector IRSensor::VectorXYfromPulseWidth(float pulseWidth[]){
  Vector rslt = {0, 0};
  for(int i = 0; i < IR_NUM; i++) {
      rslt.x += pulseWidth[i] * unitVectorX[i];
      rslt.y += pulseWidth[i] * unitVectorY[i];
  }
  return rslt;
}

Vector IRSensor::VectorRTfromXY(Vector *vectorXY_t) {
    Vector rslt;
    rslt.radius  = sqrt(pow(vectorXY_t->x, 2.0) + pow(vectorXY_t->y, 2.0));
    rslt.theta   = atan2(vectorXY_t->x, vectorXY_t->y) / PI * 180.0;

    return rslt;
}
