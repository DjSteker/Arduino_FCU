#include <BMP180.h>
#include <Wire.h>
float p,t;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  BMP180_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
//  BMP180_ReadData(&p, &t);
  p = BMP180_GetAltitude();
  Serial.println(p);
  delay(100);
}
