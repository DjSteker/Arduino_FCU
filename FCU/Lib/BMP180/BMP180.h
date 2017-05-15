#ifndef BMP180_H_INCLUDED
#define BMP180_H_INCLUDED

#include <arduino.h>
#include <Wire.h>
#define BMP180_Address 0x77

void BMP180_Init();
void BMP180_ReadCalibration();
void BMP180_ReadData(float *press, float *temp);
float BMP180_GetAltitude();
#endif // BMP180_H_INCLUDED
