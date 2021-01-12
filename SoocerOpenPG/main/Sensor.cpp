#include "Sensor.h"

void OpenMV_Value(int *angle, int *distance)
{
  int temp = 0;
  int8_t count = 0;
  char buff[INT_BUF] = {0};
  int16_t value = 0;
  Wire.requestFrom(0x12, 2);
  if (Wire.available() == 2)
  {
    count = Wire.read() | (Wire.read() << 8);
    Wire.requestFrom(0x12, count);
    if (Wire.available() == count)
    { // got full message?
      temp = 0;
      while (Wire.available())
        buff[temp++] = Wire.read();
    }
    else
    {
      while (Wire.available())
        Wire.read();
    }
  }
  else
  {
    while (Wire.available())
      Wire.read();
  }
  value = atoi(buff);
  *distance = value;

  Wire.requestFrom(0x12, 2);
  if (Wire.available() == 2)
  {
    count = Wire.read() | (Wire.read() << 8);
    Wire.requestFrom(0x12, count);
    if (Wire.available() == count)
    { // got full message?
      temp = 0;
      while (Wire.available())
        buff[temp++] = Wire.read();
    }
    else
    {
      while (Wire.available())
        Wire.read();
    }
  }
  else
  {
    while (Wire.available())
      Wire.read();
  }
  value = atoi(buff);
  if (value != 255)
  {
    *angle = -value - 90; //90は角度補正
    if (*angle > 180)
    {
      *angle = *angle - 360.0;
    }
    else if (*angle < -180)
    {
      *angle = *angle + 360.0;
    }
  }
  else
  {
    *angle = value;
  }
}
void LineSensor::init(uint8_t SSPin0, uint8_t SSPin1)
{
  pinMode(SS_PIN[0] = SSPin0, OUTPUT);
  pinMode(SS_PIN[1] = SSPin1, OUTPUT);
}

int LineSensor::PortBit(byte pinbit, uint8_t SS_Pin)
{
  //SPI.beginTransaction(settings);
  digitalWrite(SS_Pin, LOW);
  SPI.transfer(0b00000110 | pinbit >> 2);    // Start bit 1 , CH0 singleEnd
  byte highByte = SPI.transfer(pinbit << 6); // CH0 singleEnd
  byte lowByte = SPI.transfer(0x00);         // dummy
  digitalWrite(SS_Pin, HIGH);
  //SPI.endTransaction();
  unsigned int data = ((highByte & 0x0f) << 8) + lowByte;
  return data;
}
unsigned long startTime = 0;

int LineSensor::Read(LineSensor *Line_t, int CameraAngle)
{
  float read_data = 0;
  int temp_data = 0;
  float Sum_data = 0;
  uint8_t count = 0;
  for(int i=0;i<2;i++){
    for(int j=7;j>=0;j--){
      temp_data = PortBit(j, SS_PIN[i]);
//      volts = temp_data;//(int)(temp_data * Vref /4096);
      if(temp_data > 500){
//        Serial.print("1");
        if(i == 0){
        read_data = (7-j) * 22.5 -90;
        }else{
          read_data = (j+1) * (-22.5) -90;
          if(read_data < -180){
            read_data += 360;
          }
        }
        count += 1;
      }else {
//        Serial.print("0");
        read_data = 0;
        //11221211  10111121  
      }
      Sum_data -= read_data;
    }
//    Serial.print("\t");
  }
  if (count > 0)
  {
    startTime = millis();
  }
  if ((millis() - startTime) < 130)
  {
    return -(Sum_data / (float)count);
  }
  else
  {
    return CameraAngle;
  }
}
