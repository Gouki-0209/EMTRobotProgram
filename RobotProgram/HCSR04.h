#ifndef __HCSR04__
#define __HCSR04__

#include "setting.h"

class HCSR04Sensor {
  private:
    const uint8_t SensorTrig[HCSR04_NUM] = {};
    const uint8_t SensorEcho[HCSR04_NUM] = {};
  public:
    void setSensorPins();
    void getSensorDistance(float Duration[]);
};

#endif
