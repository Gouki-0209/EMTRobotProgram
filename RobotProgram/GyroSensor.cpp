#include "GyroSensor.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 imu(MPU6050_ADDRESS_AD0_LOW);

bool mpuInterrupt = false;

void GyroSensor::PinSet()
{
  pinMode(SW_PIN, INPUT_PULLUP);
}
int GyroSensor::Action()
{
  int GyroValue = 0;
  upload(); // ypr[]の内部情報が最新のデータに更新されます
  if (digitalRead(SW_PIN) == LOW)
  {
    attachOfset();
  }
  GyroValue = (uint8_t)(ypr[0] / PI * 128.0);
  if (GyroValue > 127)
  {
    GyroValue = GyroValue - 255;
  }
  return GyroValue;
}
void GyroSensor::setDevice()
{
  //  Serial.println("setDevice");
  imu_init2();
  imu_attachSensorOfset(75, -39, 30, 1759);
  delay(1000);
  upload();
  attachOfset();
  //  Serial.println((uint8_t)(ypr[0] / PI * 128.0));
}
void GyroSensor::imu_init1()
{
  //  Serial.println("imu_init");
  imu.initialize();
  imu.dmpInitialize();
  imu.setDMPEnabled(true);
}
void GyroSensor::imu_init2()
{
  mpuIntStatus = imu.getIntStatus();
  packetSize = imu.dmpGetFIFOPacketSize();
}
void dmpDataReady()
{
  mpuInterrupt = true;
}
void GyroSensor::imu_attachSensorOfset(int16_t XG, int16_t YG, int16_t ZG, int16_t ZA)
{
  //  Serial.println("imu_attachSensorOfset");
  imu.setXGyroOffset(XG);
  imu.setYGyroOffset(YG);
  imu.setZGyroOffset(ZG);
  imu.setZAccelOffset(ZA);
}

void GyroSensor::attachOfset()
{
  //  Serial.println("attachOfset");
  for (int i = 0; i < 3; ++i)
  {
    ofset_ypr[i] = raw_ypr[i];
  }
}

void GyroSensor::upload()
{
  //  Serial.println("upload");
  while (mpuInterrupt == false && fifoCount < packetSize)
    ;
  mpuInterrupt = false;

  mpuIntStatus = imu.getIntStatus();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024)
  {
    imu.resetFIFO();
  }

  while (fifoCount < packetSize)
    fifoCount = imu.getFIFOCount();

  fifoBuffer[64] = 0;
  imu.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;

  Quaternion _quaternion;
  VectorFloat _gravity;
  imu.dmpGetQuaternion(&_quaternion, fifoBuffer);
  imu.dmpGetGravity(&_gravity, &_quaternion);
  imu.dmpGetYawPitchRoll(raw_ypr, &_quaternion, &_gravity);

  for (int i = 0; i < 3; ++i)
  {
    ypr[i] = raw_ypr[i] - ofset_ypr[i];
    if (ypr[i] > PI)
      ypr[i] -= 2 * PI;
    if (ypr[i] < -PI)
      ypr[i] += 2 * PI;
  }
}
