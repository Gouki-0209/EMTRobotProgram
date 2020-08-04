#include "sensor_control.h"
#include "moving_average.h"
#include "IRSensor.h"
#include "HCSR04.h"

IRSensor IR;
HCSR04Sensor HCSR04;

void HCSR04SensorControl(float Distance[]){
  float Duration[HCSR04_NUM];
  HCSR04.getSensorDistance(Duration);
  for(int i=0;i < HCSR04_NUM;i++){
    if(Duration[i] > 0){
      Duration[i] = Duration[i]/2;
      Distance[i] = Duration[i]*340*100/1000000;
    }
  }
}

Vector IRSensorControl(){
  Vector vectorRT;
  Vector vectorXY;
  float pulseWidth[IR_NUM];
  IR.getSensorPulseWidth(pulseWidth);
  vectorXY = IR.VectorXYfromPulseWidth(pulseWidth);
  vectorRT = IR.VectorRTfromXY(&vectorXY);
  return vectorRT;
}
