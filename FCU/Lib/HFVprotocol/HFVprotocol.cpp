#include "HFVprotocol.h"

typedef union _f2b{
  float F;
  uint8_t b[4];
}F2B;

void AttitudePackage(uint8_t *DataBuffer, float Roll, float Pitch, float Yaw, float Height)
{
    F2B Roll2Send, Pitch2Send, Yaw2Send, Height2Send;
    Roll2Send.F = Roll;
    Pitch2Send.F = Pitch;
    Yaw2Send.F = Yaw;
    Height2Send.F = Height;

    uint8_t dataLength = 20;

    for(int i=3;i<7;i++)
      DataBuffer[i] = Roll2Send.b[i-3];
    for(int i=7;i<11;i++)
      DataBuffer[i] = Pitch2Send.b[i-7];
    for(int i=11;i<15;i++)
      DataBuffer[i] = Yaw2Send.b[i-11];
    for(int i=15;i<19;i++)
      DataBuffer[i] = Height2Send.b[i-15];
    DataBuffer[0] = '^';
    DataBuffer[1] = dataLength;
    DataBuffer[2] = 'A';

    DataBuffer[dataLength-1] = 0;

    for(int i=2;i<dataLength-1;i++)
      DataBuffer[dataLength-1] += DataBuffer[i];
}
