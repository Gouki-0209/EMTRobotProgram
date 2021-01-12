#include "Move.h"

#include "GyroSensor.h"
#include "Sensor.h"


def_func GyroObject;

unsigned int count_loop = 0;

extern LineSensor Line;

int MoveLoop(int Angle){
  if(Angle > -10 && Angle < 10){
    Angle += 0; 
  } else if(-180 < Angle && Angle < -10){
    Angle -= 90;
  } else if(10 < Angle && Angle < 180){
    Angle += 90;
  }
  return Angle;
}
//unsigned long Kick_startT = 0;
void move_func(MotorPins Motor[], int GyroAngle, int Speed, bool kick_flag){
  static int CameraAngle = 0, CameraDistance = 0;
  static int value[3] = {};
//  GyroAngle = GyroObject.PID(GyroAngle, 0.0);
  if(count_loop % 10 == 0){
    OpenMV_Value(&CameraAngle, &CameraDistance);
  }
  count_loop++;
//  CameraAngle = MoveLoop(CameraAngle);
  CameraAngle = Line.Read(&Line, CameraAngle);
//  CameraAngle = 90;
  if(CameraAngle != 255){
    value[0] = Speed * sin((CameraAngle + 60) * PI / 180);
    value[1] = Speed * sin((CameraAngle - 180) * PI / 180);                                                                     
    value[2] = Speed * sin((CameraAngle - 60) * PI / 180);
  }
  Motor_spin(Motor[0], value[0]+(0-GyroAngle*1.7));//右前
  Motor_spin(Motor[1], value[1]+(0-GyroAngle*1.7));//後ろ
  Motor_spin(Motor[2], -(value[2]+(0-GyroAngle*1.7)));//左前
  
  if(kick_flag){  //&& (millis()-Kick_startT)<100){
    if(-10 < CameraAngle && CameraAngle < 10){
      Kick(kpn);
      delay(10);
      //Kick_startT = millis();
    }
  }
}
