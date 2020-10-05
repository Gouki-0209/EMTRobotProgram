#include "MoveLoop.h"
#include "LineSensor.h"

extern HardwareSerial mySerial1;
extern HardwareSerial mySerial2;
extern BluetoothSerial SerialBT;

ShareObject GyroObject;
ShareObject IRANGLE;
ShareObject IRDISTANCE;
LineSensor Line;

char SetModeWord[10] = {};
bool SerialMode = false;
unsigned int SetSpeed = 0;
unsigned int SetThreshold = 0;

template void background(int SerialPrintValue);
template void background(byte SerialPrintValue);

int EEPROM_load(){
  int GetSpeed = 0;
  int GetThreshold = 0;
  EEPROM.get(1, GetThreshold);
  EEPROM.get(10, GetSpeed);
  GetSpeed = GetSpeed>0?GetSpeed:DEFAULT_SPEED;
  GetThreshold = GetThreshold>0?GetThreshold:DEFAULT_THRESHOLD;
//  Serial.print(GetSpeed);
//  Serial.print("\t");
//  Serial.println(GetThreshold);
  mySerial1.write(GetThreshold);
  return GetSpeed;
}
template <class T>void background(T SerialPrintValue){
  char str[4];
  if(SerialBT.available() >= 4){
    int8_t Buffer = SerialBT.available();
    for(int i = 0;i < Buffer;i++){
      SetModeWord[i] = SerialBT.read();
    }
    SerialBT.print(SetModeWord);
  }
  if(strncmp(SetModeWord, "line", 4) == 0) {
    if(SerialBT.available() > 0){
      for(int i = 0;i < 3;i++){
        str[i] = SerialBT.read();
      }
      SetThreshold = atoi(str);
      if(SetSpeed <= UINT8_MAX){
        SerialBT.print("set : ");
        SerialBT.println(SetThreshold);
        EEPROM.put(1, SetThreshold); // SetThreshold
        EEPROM.commit();
        memset(SetModeWord,'\0',sizeof(SetModeWord));
      } else {
        SerialBT.println("overflow");
      }
    } else {
      SerialBT.println("Please");
      delay(1000);
    }
  } else if (strncmp(SetModeWord, "motor", 5) == 0) { 
    if(SerialBT.available() > 0){
      for(int i = 0;i < 3;i++){
        str[i] = SerialBT.read();
      }
      SetSpeed = atoi(str);
      if(SetSpeed <= UINT8_MAX){
        SerialBT.print("set : ");
        SerialBT.println(SetSpeed);
        EEPROM.put(10, SetSpeed);
        EEPROM.commit();
        memset(SetModeWord,'\0',sizeof(SetModeWord));
      } else {
        SerialBT.println("overflow");
      }
    } else {
      SerialBT.println("Please");
      delay(1000);
    }
  } else if (strncmp(SetModeWord, "value", 5) == 0){
    SerialMode = true;
  } else if (strncmp(SetModeWord, "stop", 4) == 0){
    SerialMode = false;
  }
  if(SerialMode){
    SerialBTPrint(SerialPrintValue);
  }
}
void SerialBTPrint(int value){
  SerialBT.println(value);
  delay(1000);
}
void SerialBTPrint(byte value){
  SerialBT.println(value, BIN);
}
//int MotorSpeedSet(){
//  char str[4];
//  int Speed = 0;
//  while(!SerialBT.available()){
//    SerialBT.println("Please enter the speed of the motor");
//    delay(1500);
//  }
//  if(SerialBT.available() > 0){
//    for(int i = 0; i<3; i++){
//      str[i] = SerialBT.read();
//    }
//    Speed = atoi(str);
//  }
//  SerialBT.print("set the speed of the motor : ");
//  SerialBT.println(Speed);
//  return Speed;  
//}
//void LineThresholdSet(){
//  char str[4];
//  uint8_t Value = 0;
//  while(!SerialBT.available()){
//    SerialBT.println("Please enter the threshold of the linesensor");
//    delay(1500);
//  }
//  if(SerialBT.available() > 0){
//    for(int i = 0; i<3; i++){
//      str[i] = SerialBT.read();
//    }
//    Value = atoi(str);
//  }
//  SerialBT.print("set the threshold of the linesensor : ");
//  SerialBT.println(Value);
//  mySerial1.write(Value);
//}
void LineSerialReceive(byte *LineData){
  if (mySerial1.available() > 0) {
    *LineData = mySerial1.read();
  }
}
bool IRSerialReceive(IRInfo_t *rslt){

  if (mySerial2.available() > 3) {
    if((int8_t)mySerial2.read() == -128){
      rslt->theta = (int8_t)mySerial2.read() * 180.0 / 127.0;  //±127の範囲から±180の範囲に変換
      rslt->radius = (int8_t)mySerial2.read();
      return true;
    }
  }

//  Serial.println(rslt.theta);
//  Serial.print("\t");
//  Serial.print(radius);
  return false;
}
void MotorSerialWrite(int GyroAngle, int IRAngle, int IRDistance, byte LineByte, int Speed){ 
  GyroAngle = GyroObject.PID(GyroAngle, 0);
  IRAngle = IRANGLE.LPF(IRAngle, 0.5);
  IRDistance = IRDISTANCE.LPF(IRDistance, 0.5);
  IRAngle = MoveLoop(IRAngle, IRDistance);
  IRAngle = Line.upload(LineByte, IRAngle);
//  Serial.print("\t");
//  Serial.println(IRAngle);
  
  int value[3];
  value[0] = -Speed * sin((IRAngle - 60) * PI / 180);
  value[1] = -Speed * sin((IRAngle + 60) * PI / 180);
  value[2] = -Speed * sin((IRAngle -180) * PI / 180);
  
//  Serial.print(value[0]);
//  Serial.print("\t");
//  Serial.print(value[2]);
//  Serial.print("\t");
//  Serial.println(value[1]);

//  Serial.println(GyroAngle);
  
  mySerial1.write(-128);
  mySerial1.write(GyroAngle + value[0]); //右前
  mySerial1.write(GyroAngle + value[2]); //後ろ
  mySerial1.write(GyroAngle + value[1]); //左前
}
int MoveLoop(int Angle, int Distance){
  if(Distance > 35){
    if(Angle > -10 && Angle < 10){
      Angle = 0; 
    } else if(-180 < Angle && Angle < -10){
      Angle -= 90;
    } else if(10 < Angle && Angle < 180){
      Angle += 90;
    }
  }
  return Angle;
}
