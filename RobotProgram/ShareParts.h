#ifndef __SHAREPARTS__
#define __SHAREPARTS__

#include "Arduino.h"
#include <Wire.h>
#include "BluetoothSerial.h"
#include <EEPROM.h>

#define IR_NUM 12
#define HCSR04_NUM 4
#define StartPin 25

#define UINT8_MAX 256

#define DEFAULT_SPEED 80
#define DEFAULT_THRESHOLD 65

#define Kp 1.5
#define Ki 0.01
#define Kd 0.1

typedef struct {
  float x;
  float y;
  float radius;
  float theta;
} Vector;

const float unitVectorX[IR_NUM] = {0.000, 0.500, 0.866, 1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500};
const float unitVectorY[IR_NUM] = {1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500, 0.000, 0.500, 0.866};
const float deltaPulseWidth     = 2.0;

class ShareObject {
  private:
    int PreY = 0;
    double duty = 0;
    double dt, preTime;
    double P, I = 0, D, preP = 0;
  public:
    int LPF(int Value, float a);
    int PID(double value,double target);
};




#endif
