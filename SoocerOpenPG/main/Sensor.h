#ifndef __SENSOR__
#define __SENSOR__

#include "ShareObject.h"

#define INT_BUF 10

void OpenMV_Value(int *angle, int *distance);

class LineSensor{
    private:
        uint8_t SS_PIN[2];
    public:
        void init(uint8_t SSPin0, uint8_t SSPin1);
        int PortBit(byte pinbit, uint8_t SS_Pin);
        int Read(LineSensor *Line_t, int CameraAngle);
        
};
#endif
