#include "Sensor.h"

void OpenMV_Value(int *angle, int *distance){
  int temp = 0;
  int8_t count = 0;
  char buff[INT_BUF] = {0};
  int16_t value = 0;
  Wire.requestFrom(0x12, 2);
  if(Wire.available() == 2){
    count = Wire.read() | (Wire.read() << 8);
    //delay(1); // Give some setup time...
    Wire.requestFrom(0x12, count);
    if(Wire.available() == count) { // got full message?
      temp = 0;
      while(Wire.available()) buff[temp++] = Wire.read();
    } else {
      while(Wire.available()) Wire.read();
    }
  } else {
    while(Wire.available()) Wire.read();
  }
  value = atoi(buff);
//  Serial.print(temp);
//  Serial.print("\t");
//  Serial.print(value);
//  Serial.print("\t");
  //if(value != 255){
    *distance = value;
//  }else{
//    *distance = value;
//  }
  
  Wire.requestFrom(0x12, 2);
  if(Wire.available() == 2){
    count = Wire.read() | (Wire.read() << 8);
    //delay(1); // Give some setup time...
    Wire.requestFrom(0x12, count);
    if(Wire.available() == count){ // got full message?
      temp = 0;
      while(Wire.available()) buff[temp++] = Wire.read();
      
      //buff = (int)Wire.read();
    } else {
      while(Wire.available()) Wire.read();
    }
  } else {
    while(Wire.available()) Wire.read();
  }
  value = atoi(buff);
//  Serial.print(count);
//  Serial.print("\t");
//  Serial.println(value);
  if(value != 255){
    *angle = -value-90;//90は角度補正
    if (*angle > 180){
      *angle = *angle - 360.0;
    }else if(*angle < -180){
      *angle = *angle + 360.0;
    }
  }else {
    *angle = value;
  }
}
