#include <Wire.h>
#include <MPU6050.h>
#include <HMC5883L.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  Wire.begin();
  MPU6050_Init();
  MPU6050_I2C_Bypass(true);
  delay(100);
  HMC5883L_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  float angle = HMC5883L_GetDirection();
  Serial.print("Dir(deg):");
  Serial.println(angle);
  delay(100);
}
