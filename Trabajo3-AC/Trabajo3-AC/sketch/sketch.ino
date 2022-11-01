#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); 
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
}

void loop()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  uint8_t arr[12] = {0};

  memcpy(arr,(uint8_t *)&a.acceleration.x,4);
  memcpy(arr+4,(uint8_t *)&a.acceleration.y,4);
  memcpy(arr+8,(uint8_t *)&a.acceleration.z,4);

    if(Serial.available() > 0)
    {
      String res = Serial.readStringUntil('\n');

      if(res == "j")
      {
        Serial.write(arr,12);
      }
    }
    delay(100);
}