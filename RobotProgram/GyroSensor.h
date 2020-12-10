#ifndef __GYROSENSOR__
#define __GYROSENSOR__

#include "ShareParts.h"

#define INT_PIN 19
#define SW_PIN 26

class GyroSensor
{
private:
  uint16_t packetSize;
  uint16_t fifoCount;
  uint8_t fifoBuffer[1024];
  uint8_t mpuIntStatus;
  float raw_ypr[3], ofset_ypr[3], ypr[3];

public:
  void PinSet();
  int Action();
  void setDevice();
  void imu_init1();
  void imu_init2();
  void imu_attachSensorOfset(int16_t XG, int16_t YG, int16_t ZG, int16_t ZA);
  
  void attachOfset();
  void upload();
};
void dmpDataReady();
#endif
