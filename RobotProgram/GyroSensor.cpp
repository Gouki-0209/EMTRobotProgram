#include "GyroSensor.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 imu(MPU6050_ADDRESS_AD0_LOW);

void GyroSensor::setDevice(){
  imu_init();
  imu_attachSensorOfset(146, 57, -36, 1017);
  upload();
  attachOfset();
  Wire.begin();
  Wire.setClock(400000);
}

void GyroSensor::imu_init()
{
  imu.initialize();
  imu.dmpInitialize();
  imu.setDMPEnabled(true);
  
  //attachInterrupt(digitalPinToInterrupt(INT_PIN), dmpDataReady, RISING);
  mpuIntStatus = imu.getIntStatus();
  packetSize = imu.dmpGetFIFOPacketSize();
}

void GyroSensor::imu_attachSensorOfset(int16_t XG, int16_t YG, int16_t ZG, int16_t ZA)
{
  imu.setXGyroOffset(XG);
  imu.setYGyroOffset(YG);
  imu.setZGyroOffset(ZG);
  imu.setZAccelOffset(ZA);
}

void GyroSensor::dmpDataReady()
{
  mpuInterrupt = true;
}

void GyroSensor::attachOfset()
{
  for (int i = 0; i < 3; ++i) {
    ofset_ypr[i] = raw_ypr[i];
  }
}

void GyroSensor::upload()
{

  while (mpuInterrupt == false && fifoCount < packetSize);
  mpuInterrupt = false;

  mpuIntStatus = imu.getIntStatus();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    imu.resetFIFO();
  }

  while (fifoCount < packetSize) fifoCount = imu.getFIFOCount();

  fifoBuffer[64] = 0;
  imu.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;

  Quaternion _quaternion;
  VectorFloat _gravity;
  imu.dmpGetQuaternion(&_quaternion, fifoBuffer);
  imu.dmpGetGravity(&_gravity, &_quaternion);
  imu.dmpGetYawPitchRoll(raw_ypr, &_quaternion, &_gravity);

  for (int i = 0; i < 3; ++i) {
    ypr[i] = raw_ypr[i] - ofset_ypr[i];
    if(ypr[i] >  PI) ypr[i] -= 2 * PI;
    if(ypr[i] < -PI) ypr[i] += 2 * PI;
  }
}
