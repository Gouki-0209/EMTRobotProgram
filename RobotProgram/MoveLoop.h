#ifndef __MOVELOOP__
#define __MOVELOOP__

#include "ShareParts.h"

typedef struct {
  int theta;
  int radius;
} IRInfo_t;

int EEPROM_load();
template <class T>void background(T SerialPrintValue); 
void SerialBTPrint(int value);
void SerialBTPrint(byte value);
//int MotorSpeedSet();
//void LineThresholdSet();
void LineSerialReceive(byte *LineData);
bool IRSerialReceive(IRInfo_t *rslt);
void MotorSerialWrite(int GyroAngle, int IRAngle, int IRDistance, byte LineByte, int Speed);
int MoveLoop(int Angle, int Distance);

#endif 
