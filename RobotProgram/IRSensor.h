#ifndef __IRSENSOR__
#define __IRSENSOR__

#include "setting.h"

class IRSensor {
  private:
    const uint8_t SensorPins[IR_NUM] = {17,18,19,16,15,14,9,8,7,6,5,4};
  public:
    void setSensorPins();
    void getSensorPulseWidth(float pulseWidth[]);
    Vector VectorXYfromPulseWidth(float pulseWidth[]);
    Vector VectorRTfromXY(Vector *vectorRX_t);
};

#endif
