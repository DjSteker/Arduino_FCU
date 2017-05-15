#include <HMC5883L.h>

int16_t Max_temp[3] = {1}, min_temp[3] = {-1};

void HMC5883L_Init()
{
    Wire.beginTransmission(0x1E);
    Wire.write(0x00);
    Wire.write(0x74);
    Wire.write(0x02);
    Wire.write(0x00);
    Wire.endTransmission(true);
}

float HMC5883L_GetDirection()
{
    return HMC5883L_GetDirection_With_Tilt(.0f, .0f);
}

float HMC5883L_GetDirection_With_Tilt(float Roll, float Pitch)
{
    int16_t rawData[3], offset[3];
    float scale[3], norm[3];

    Wire.beginTransmission(0x1E);
    Wire.write(0x03);
    Wire.endTransmission(false);
    Wire.requestFrom(0x1E, 6, true);
    if(Wire.available() <= 6)
    {
        rawData[0] = Wire.read() << 8 | Wire.read();
        rawData[1] = Wire.read() << 8 | Wire.read();
        rawData[2] = Wire.read() << 8 | Wire.read();
    }

    for(int i=0;i<3;i++)
    {
        if(rawData[i] > Max_temp[i])
            Max_temp[i] = rawData[i];
        else if(rawData[i] < min_temp[i])
            min_temp[i] = rawData[i];

        scale[i] = ((float)(Max_temp[i]-min_temp[i]))/2.0f;
        offset[i] = (int16_t)(scale[i] + min_temp[i]);
        norm[i] = ((float)(rawData[i]-offset[i]))/scale[i];
    }

    if(norm[0] <= 1.0f && norm[0] >= -1.0f && norm[1] <= 1.0f && norm[1] >= -1.0f && norm[2] <= 1.0f && norm[2] >= -1.0f)
    {
        Roll = Roll * M_PI / 180.0f; Pitch = Pitch * M_PI / 180.0f;
        float Hx = norm[0] * cos(Pitch) + norm[2] * sin(Roll) * sin(Pitch) - norm[1] * cos(Roll) * sin(Pitch);
        float Hy = norm[2] * cos(Roll) + norm[1] * sin(Roll);
        float angle = atan2(Hy, Hx) / M_PI * 180.0;
        if(angle < 0.0f)
            angle += 360.0f;
        return angle;
    }
    else
        return .0f;
}
