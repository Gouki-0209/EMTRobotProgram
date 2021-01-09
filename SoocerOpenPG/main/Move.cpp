#include "Move.h"

#include "GyroSensor.h"
#include "Sensor.h"

def_func GyroObject;

unsigned int count_loop = 0;

void move_func(MotorPins Motor[], int GyroAngle, int Speed){
  static int CameraAngle = 0, CameraDistance = 0;
  static int value[3] = {};
  GyroAngle = GyroObject.PID(GyroAngle, 0.0);
  if(count_loop % 10 == 0){
    OpenMV_Value(&CameraAngle, &CameraDistance);
  }
  count_loop++;
//  Serial.println(CameraAngle);
  if(CameraAngle != 255){
    value[0] = -Speed * sin((CameraAngle + 60) * PI / 180);
    value[1] = -Speed * sin((CameraAngle + 180) * PI / 180);                                                                     
    value[2] = Speed * sin((CameraAngle - 60) * PI / 180);
  }
  Motor_spin(Motor[0], value[0]+GyroAngle);
  Motor_spin(Motor[1], value[1]-GyroAngle);
  Motor_spin(Motor[2], value[2]+GyroAngle);
}
