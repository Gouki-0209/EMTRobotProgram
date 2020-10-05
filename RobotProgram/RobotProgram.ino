#include "MoveLoop.h"
#include "GyroSensor.h"

BluetoothSerial SerialBT;
HardwareSerial mySerial1(1);
HardwareSerial mySerial2(2);
GyroSensor Gyro;
IRInfo_t IRInfo;

int MotorSpeed = 0;
int Threshold = 0;
byte LineData;
int GyroValue;

void setup() {
  
  Gyro.PinSet();
  
  pinMode(StartPin, INPUT_PULLUP);
  
  SerialBT.begin("ESP32-EMT");
  Serial.begin(115200);
  mySerial1.begin(9600, SERIAL_8N1, 32, 33);
  mySerial2.begin(9600);
  Wire.begin();
  Wire.setClock(400000);
  EEPROM.begin(1024);
  
  Gyro.imu_init1(); //imu_init1()とimu_init2()の間に割り込み設定が必要
  attachInterrupt(digitalPinToInterrupt(INT_PIN), dmpDataReady, RISING);
  Gyro.setDevice();
  MotorSpeed = EEPROM_load();
//  MotorSpeed = MotorSpeedSet();
//  LineThresholdSet();
}

void loop() {
  background(LineData);
  GyroValue = Gyro.Action();
  LineSerialReceive(&LineData);
  if(digitalRead(StartPin) == HIGH){
    if(IRSerialReceive(&IRInfo)){
//      Serial.println(IRInfo.radius);
      if(IRInfo.radius > 0){
        MotorSerialWrite(GyroValue, IRInfo.theta, IRInfo.radius, LineData, (int)MotorSpeed);
      } else {
        MotorSerialWrite(GyroValue, IRInfo.theta, IRInfo.radius, LineData, 0);
      }
    } 
  } else {
    MotorSerialWrite(0, 0, 0, 0, 0);
  }
}

void dmpDataReady()
{
  Gyro.mpuInterrupt = true;
}
