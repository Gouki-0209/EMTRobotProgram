#include "GyroSensor.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 imu(MPU6050_ADDRESS_AD0_LOW);
Quaternion _quaternion;
VectorFloat _gravity;

void GyroSensor::setDevice()
{
    pinMode(SW_PIN, INPUT_PULLUP);
    //  Serial.println("setDevice");
    imu_init();
    imu_attachSensorOffset(75, -39, 30, 1759);
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

    packetSize = imu.dmpGetFIFOPacketSize();
}

int GyroSensor::getGyroValue()
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
    if (fifoCount == 1024)
    {
        imu.resetFIFO();
    }

    while (fifoCount < packetSize)
    {
        fifoCount = imu.getFIFOCount();
    }

    fifoBuffer[64] = 0;
    imu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;

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
