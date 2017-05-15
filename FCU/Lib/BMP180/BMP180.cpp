#include "BMP180.h"

int16_t c_AC1, c_AC2, c_AC3, c_B1, c_B2, c_MB, c_MC, c_MD;
uint16_t c_AC4, c_AC5, c_AC6;

void BMP180_Init(){
    BMP180_ReadCalibration();
}

void BMP180_ReadCalibration(){
    Wire.beginTransmission(BMP180_Address);
    Wire.write(0xAA);
    Wire.endTransmission(false);
    Wire.beginTransmission(BMP180_Address);
    Wire.requestFrom(BMP180_Address, 22, true);

    uint8_t buffer[22];
    while(Wire.available())
    {
        for(uint8_t i = 0; i < 22; i++)
        {
            buffer[i] = Wire.read();
        }
    }
	// This data is in Big Endian format from the BMP180.
    c_AC1 = (buffer[0] << 8) | buffer[1];
    c_AC2 = (buffer[2] << 8) | buffer[3];
    c_AC3 = (buffer[4] << 8) | buffer[5];
    c_AC4 = (buffer[6] << 8) | buffer[7];
    c_AC5 = (buffer[8] << 8) | buffer[9];
    c_AC6 = (buffer[10] << 8) | buffer[11];
    c_B1 = (buffer[12] << 8) | buffer[13];
    c_B2 = (buffer[14] << 8) | buffer[15];
    c_MB = (buffer[16] << 8) | buffer[17];
    c_MC = (buffer[18] << 8) | buffer[19];
    c_MD = (buffer[20] << 8) | buffer[21];
}
void BMP180_ReadData(float *press, float *temp)
{
    int16_t UT;
    long UP;

    Wire.beginTransmission(BMP180_Address);
    Wire.write(0xF4);
    Wire.write(0x2E);
    Wire.endTransmission(true);

    delay(5);

    Wire.beginTransmission(BMP180_Address);
    Wire.write(0xF6);
    Wire.endTransmission(false);
    Wire.beginTransmission(BMP180_Address);
    Wire.requestFrom(BMP180_Address, 2, true);
    UT = Wire.read()<<8 | Wire.read();

    Wire.beginTransmission(BMP180_Address);
    Wire.write(0xF4);
    Wire.write(0x34);
    Wire.endTransmission(true);

    delay(4);

    Wire.beginTransmission(BMP180_Address);
    Wire.write(0xF6);
    Wire.endTransmission(false);
    Wire.beginTransmission(BMP180_Address);
    Wire.requestFrom(BMP180_Address, 3, true);
    uint8_t buffer[3];
    UP = ((((long)Wire.read() <<16) | ((long)Wire.read() <<8) | ((long)Wire.read())) >> 8);

    int temperature;
    long X2;
	long X1;
	X1 = (((long)UT - (long)c_AC6) * (long)c_AC5) >> 15;
    X2 = ((long)c_MC << 11) / (X1 + c_MD);
    int B5 = X1 + X2;
    temperature = (int)((B5 + 8) >> 4);
    *temp = temperature/10;

    long B6 = B5 - 4000;
    X1 = (c_B2 * (B6 * B6) >> 12) >> 11;
    X2 = (c_AC2 * B6) >> 11;
    long X3 = X1 + X2;
    long B3 = (((((long)c_AC1) * 4 + X3) << 0) + 2) >> 2;
    X1 = (c_AC3 * B6) >> 13;
    X2 = (c_B1 * (B6 * B6 >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    long B4 = (c_AC4 * (unsigned long)((X3 + 32768))) >> 15;
    unsigned long B7 = (unsigned long)(((UP - B3)) * (50000 >> 0));
    long p;
    if (B7 < 0x80000000)
	{
		p = ((B7 * 2) / B4);
	}
    else
	{
        p = ((B7 / B4) << 1);
	}

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;
    *press = p + ((X1 + X2 + 3791) >> 4);
}

float BMP180_GetAltitude()
{
    // Get pressure in Pascals (Pa).
    float pressure, temperature;
    BMP180_ReadData(&pressure, &temperature);
    // Calculate altitude from sea level.
    float altitude = 44330.0 * (1.0 - pow(pressure / 101325.0, 0.1902949571836346));
    return altitude;
}
