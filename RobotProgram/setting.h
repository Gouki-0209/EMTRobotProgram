#ifndef __SETTING__
#define __SETTING__

#include "Arduino.h"
#include <Wire.h>

#define IR_NUM 12
#define HCSR04_NUM 4

typedef struct {
  float x;
  float y;
  float radius;
  float theta;
} Vector;

const float unitVectorX[IR_NUM] = {0.000, 0.500, 0.866, 1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500};
const float unitVectorY[IR_NUM] = {1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500, 0.000, 0.500, 0.866};
const float deltaPulseWidth     = 2.0;



#endif
