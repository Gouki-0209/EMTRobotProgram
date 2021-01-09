#include "GyroSensor.h"
#include "Move.h"
GyroSensor Gyro;
MotorPins Motor[3];
#define TL_Switch 16
#define MotorSpeed 160
void setup()
{
    pinMode(TL_Switch, INPUT_PULLUP);
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(400000);
    Gyro.imu_init();
    attachInterrupt(digitalPinToInterrupt(INT_PIN), dmpDataReady, RISING);
    Gyro.setDevice();
    set_Motor_channel(3);
    set_Motor_pin(Motor[0], 14, 32, 0);
    set_Motor_pin(Motor[1], 26, 33, 1);
    set_Motor_pin(Motor[2], 27, 25, 2);
    //Gyro_init();
}
void loop()
{
    int angle = Gyro.getGyroValue();
    Serial.println(angle);
    delay(10);
//    if(TL_Switch == HIGH){
//      move_func(Motor, angle, MotorSpeed);
//    }else{
      move_func(Motor, angle, 0);
//    }
}
