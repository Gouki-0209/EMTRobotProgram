#include "GyroSensor.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 imu(MPU6050_ADDRESS_AD0_LOW);
Quaternion _quaternion;
VectorFloat _gravity;

bool mpuInterrupt = false;

void GyroSensor::setDevice()
{
    pinMode(SW_PIN, INPUT);
    mpuIntStatus = imu.getIntStatus();
    packetSize = imu.dmpGetFIFOPacketSize();
    imu_attachSensorOffset(80, -33, 4, 894);
    delay(1000);


    upload();
    attachOffset();
    //  Serial.println((uint8_t)(ypr[0] / PI * 128.0));
}

void GyroSensor::imu_init()
{
    //  Serial.println("imu_init");
    imu.initialize();
    imu.dmpInitialize();
    imu.setDMPEnabled(true);

}
void dmpDataReady()
{
  mpuInterrupt = true;
}
//int Pre_Buff[3] = {};
//int count = 0;

//void swap (int *x, int *y) {
//  int temp;    // 値を一時保存する変数
//
//  temp = *x;
//  *x = *y;
//  *y = temp;
//}
//void bubble_sort (int array[], int array_size) {
//  int i, j;
//
//  for (i = 0; i < array_size - 1; i++){
//    for (j = array_size - 1; j >= i + 1; j--){   //　右から左に操作
//      if (array[j] < array[j-1]) { swap(&array[j], &array[j-1]); }
//    }
//  }
//}
//}
int PreData = 0;
int GyroSensor::getGyroValue()
{
    def_func Gyro;
    int GyroValue = 0;
    int sendData = 0;
    upload(); // ypr[]の内部情報が最新のデータに更新されます
    if (digitalRead(SW_PIN) == HIGH)
    {
        attachOffset();
    }
    GyroValue = (int8_t)(ypr[0] / PI * 128.0);
    
   if(abs(PreData-GyroValue) > 25){
      sendData = PreData;
    } else {
      sendData = GyroValue;
    }
    PreData = sendData;
    return -sendData;
}

void GyroSensor::imu_attachSensorOffset(int16_t XG, int16_t YG, int16_t ZG, int16_t ZA)
{
    //  Serial.println("imu_attachSensorOffset");
    imu.setXGyroOffset(XG);
    imu.setYGyroOffset(YG);
    imu.setZGyroOffset(ZG);
    imu.setZAccelOffset(ZA);
}

void GyroSensor::attachOffset()
{
    //  Serial.println("attachOffset");
    for (int i = 0; i < 3; ++i)
    {
        offset_ypr[i] = raw_ypr[i];
    }
}

void GyroSensor::upload()
{
  //  Serial.println("upload");
  if (mpuInterrupt == false && fifoCount < packetSize){
    return;
  }
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
    ypr[i] = raw_ypr[i] - offset_ypr[i];
    if (ypr[i] > PI)
      ypr[i] -= 2 * PI;
    if (ypr[i] < -PI)
      ypr[i] += 2 * PI;
  }
}
