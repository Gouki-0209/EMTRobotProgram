#ifndef __GYROSENSOR__
#define __GYROSENSOR__

#include "ShareObject.h"

#define SW_PIN 35
#define INT_PIN 15

class GyroSensor
{
private:
    uint16_t packetSize;
    uint16_t fifoCount;
    uint8_t fifoBuffer[1024];
    float raw_ypr[3], offset_ypr[3], ypr[3];
    uint8_t mpuIntStatus;
public:
    void PinSet();
    void setDevice();
    void imu_init();
    int getGyroValue();
    void imu_attachSensorOffset(int16_t XG, int16_t YG, int16_t ZG, int16_t ZA);
    void attachOffset();
    void upload();
};
void dmpDataReady();
#endif
