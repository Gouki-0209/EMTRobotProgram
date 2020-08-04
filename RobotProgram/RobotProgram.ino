#include "sensor_control.h"
#include "GyroSensor.h"
#include "IRSensor.h"
IRSensor IRsensor;
GyroSensor Gyro;

uint8_t pin = 18; 
void setup() {
  // put your setup code here, to run once:
  pinMode(pin, INPUT);
//  IRsensor.setSensorPins();
  Serial.begin(115200);
//  Gyro.setDevice();
}

void loop() {
  int pulse_width;
  pulse_width = pulseIn(pin, HIGH);
  Serial.println(pulse_width);
  delay(100);
}
