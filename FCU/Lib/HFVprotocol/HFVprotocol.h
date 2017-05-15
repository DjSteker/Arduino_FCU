#ifndef HFVPROTOCOL_H_INCLUDED
#define HFVPROTOCOL_H_INCLUDED

#include <inttypes.h>

void AttitudePackage(uint8_t *DataBuffer, float Roll, float Pitch, float Yaw, float Height);

#endif // HFVPROTOCOL_H_INCLUDED
