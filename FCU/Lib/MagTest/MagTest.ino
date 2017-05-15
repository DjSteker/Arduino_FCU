#include <Wire.h>
#include <MPU6050.h>
uint8_t data;
int16_t x,y,z;
int16_t Mx=300, Mz=-300, mx=300, mz=-300, My=300, my=-300;
int16_t x_offset, y_offset, z_offset;
float x_scale, y_scale, z_scale;
float norm_x, norm_y, norm_z;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  Wire.begin();
  MPU6050_Init();
  MPU6050_I2C_Bypass(true);
  delay(100);
  Wire.beginTransmission(0x1E);
  Wire.write(0x00);
  Wire.write(0x74);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x1E);
  Wire.write(0x03);
  Wire.endTransmission(false);
  Wire.requestFrom(0x1E, 6, true);
//  data = Wire.read();
  if(Wire.available() <=6) {    // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
  if(x > Mx)
    Mx = x;
  else if(x < mx)
    mx = x;
  if(y > My)
    My = y;
  else if(y < my)
    my = y;
  if(z > Mz)
    Mz = z;
  else if(z < mz)
    mz = z;
  x_offset = (int16_t)((float)(Mx-mx))/2+mx;
  x_scale = (float)((Mx-mx)/2);
  norm_x = (float)(x-x_offset)/x_scale;
  y_offset = (int16_t)((float)(My-my))/2+my;
  y_scale = (float)((My-my)/2);
  norm_y = (float)(y-y_offset)/y_scale;
  z_offset = (int16_t)((float)(Mz-mz))/2+mz;
  z_scale = (float)((Mz-mz)/2);
  norm_z = (float)(z-z_offset)/z_scale;
  
  float angle = atan2(norm_y,norm_x)/M_PI*180;
    if (angle < 0)
    {
      angle = angle + 360;
    }

//  Serial.print("x = ");Serial.print(x);
//  Serial.print(", y = ");Serial.print(y);
//  Serial.print(", z = ");Serial.println(z);
  Serial.print("Dir(deg):");
  Serial.println(angle);
  delay(100);
}
