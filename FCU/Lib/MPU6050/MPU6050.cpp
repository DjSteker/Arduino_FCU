#include <MPU6050.h>
int GyroOffset[3] = {0};
void MPU6050_Init()
{
    Wire.beginTransmission(MPU_Address);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission(true);

    for(int i=0;i<100;i++)
    {
        Wire.beginTransmission(MPU_Address);
        Wire.write(0x43);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_Address,6,true);
        GyroOffset[0]+=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        GyroOffset[1]+=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        GyroOffset[2]+=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    }
    for(int i=0;i<3;i++)
        GyroOffset[i] /= 100;
}

void MPU6050_I2C_Bypass(bool isOn)
{
    if(isOn)
    {
        Wire.beginTransmission(MPU_Address);
        Wire.write(0x37);
        Wire.write(0x02);
        Wire.write(0x6A);
        Wire.write(0x00);
        Wire.endTransmission(true);
    }
    else
    {
        Wire.beginTransmission(MPU_Address);
        Wire.write(0x37);
        Wire.write(0x00);
        Wire.write(0x6A);
        Wire.write(0x20);
        Wire.endTransmission(true);
    }
}

void MPU6050_ReadData(int16_t *AccData, int16_t *GyroData, int16_t *MPU_Temp, int16_t *AccOffset)
{
    Wire.beginTransmission(MPU_Address);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU_Address,14,true);
    *AccData=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    *(AccData+1)=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    *(AccData+2)=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    *MPU_Temp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    *GyroData=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    *(GyroData+1)=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    *(GyroData+2)=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    for(int i=0;i<3;i++)
    {
        *(GyroData+i) -= *(GyroOffset+i);
        *(AccData+i) -= *(AccOffset+i);
    }

}
