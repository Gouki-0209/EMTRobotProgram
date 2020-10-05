#ifndef __LINESENSOR__
#define __LINESENSOR__

#include "ShareParts.h"

class LineSensor {
  private:
    bool flag = true;
    unsigned long startTime = 0;
    int preAngle = 0;
  public:
    void Judgement(byte LineValue);
    int upload(byte LineValue, int IRAngle);
};

#endif
