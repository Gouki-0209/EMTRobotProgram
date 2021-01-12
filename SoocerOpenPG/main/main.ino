#include "GyroSensor.h"
#include "Move.h"
#include "Actuator.h"
#include "Sensor.h"
GyroSensor Gyro;
LineSensor Line;
MotorPins Motor[3];
#define TL_Switch 16
#define MotorSpeed 160

void setup()
{
    pinMode(TL_Switch, INPUT_PULLUP);
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);  // OpenMVとmpu6050は400000Hz

    SPI.begin(); // VSPI
    SPI.setFrequency(1000000);
    SPI.setDataMode(SPI_MODE3);

    Gyro.imu_init();    //Wire.beginの後
    attachInterrupt(digitalPinToInterrupt(INT_PIN), dmpDataReady, RISING);
    //入力ピンは不安定・esp32の場合、digitalPinToInterruptが必要
    Gyro.setDevice();

    Line.init(4, 17);

    set_Motor_channel(3);
    set_Motor_pin(Motor[0], 14, 32, 0);
    set_Motor_pin(Motor[1], 27, 33, 1);
    set_Motor_pin(Motor[2], 26, 25, 2);
    //NOT回路は0Vでも機能してしまうので、PWMを出力するだけで動いてしまう。
    set_Kicker_pin(kpn);
}
unsigned long pre_time = 0;
void loop()
{
    int angle = Gyro.getGyroValue();
    if(millis()- pre_time > 10){
    Serial.println(angle);
    if(digitalRead(TL_Switch) == LOW){
      move_func(Motor, angle, MotorSpeed, true);
    } else {
      move_func(Motor, 0,0, false);
    }
    pre_time = millis();
    }   //10msに1回
}
