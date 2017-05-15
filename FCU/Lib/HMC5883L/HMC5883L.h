#ifndef HMC5883L_H_INCLUDED
#define HMC5883L_H_INCLUDED

#include <Wire.h>
#include <math.h>

#define HMC5883L_Address 0x1E

void HMC5883L_Init();
float HMC5883L_GetDirection();
float HMC5883L_GetDirection_With_Tilt(float Roll, float Pitch);

#endif // HMC5883L_H_INCLUDED
