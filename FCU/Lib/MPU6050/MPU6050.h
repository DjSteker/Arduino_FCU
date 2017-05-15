#ifndef MPU6050_H_INCLUDED
#define MPU6050_H_INCLUDED

#include <Wire.h>

#define MPU_Address 0x68

void MPU6050_Init();
void MPU6050_I2C_Bypass(bool isOn);
void MPU6050_ReadData(int16_t *AccData, int16_t *GyroData, int16_t *MPU_Temp, int16_t *AccOffset);

#endif // MPU6050_H_INCLUDED
