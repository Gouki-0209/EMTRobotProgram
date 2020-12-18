#include <Wire.h>
void setup()
{
#ifdef DEBUG
    Serial.begin(115200);
#endif
    Wire.begin();
    //Gyro_init();
}
void Gyro_init()
{
    //Wire.begin
}
void loop()
{
#ifdef DEBUG
    Serial.println("Hello world");
    delay(1000);
#endif
}
