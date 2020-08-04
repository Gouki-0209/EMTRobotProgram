#ifndef __GYROSENSOR__
#define __GYROSENSOR__

#include "setting.h"

#define INT_PIN   19
#define SW_PIN    A14

class GyroSensor {
  private: 
    uint16_t   packetSize;
    uint16_t  fifoCount;
    uint8_t   fifoBuffer[1024];
    uint8_t   mpuIntStatus;
    float     raw_ypr[3], ofset_ypr[3], ypr[3];
    volatile bool   mpuInterrupt = false;
  public:
    void setDevice();
    void imu_init();
    void imu_attachSensorOfset(int16_t XG, int16_t YG, int16_t ZG, int16_t ZA);
    void dmpDataReady();
    void attachOfset();
    void upload();
};

#endif 
