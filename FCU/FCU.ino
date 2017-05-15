#include <MPU6050.h>
#include <BMP180.h>
#include <HMC5883L.h>
#include <matrix.h>
#include <TimedAction.h>
#include <HFVprotocol.h>
#include <Servo.h>

#define Button_Pin 2
#define RF_MD0 7
#define RF_MD1 8

void DataUpdate();
void AttitudeUpdate();
void AltitudeUpdate();
void AttitudeControl();
void OutputData();

TimedAction DataUpdate_Action = TimedAction(1, DataUpdate);
TimedAction AttitudeUpdate_Action = TimedAction(10, AttitudeUpdate);
TimedAction AltitudeUpdate_Action = TimedAction(20, AltitudeUpdate);
TimedAction AttitudeControl_Action = TimedAction(50, AttitudeControl);
TimedAction OutputData_Action = TimedAction(100, OutputData);

Servo Left_Servo, Right_Servo, Left_Motor, Right_Motor;
uint8_t Throttle = 0, x_Axis = 90, y_Axis = 90;
uint8_t t, x, y, m, a;
boolean ReceiveDone = false, AdjustDone = false; 
uint8_t ReceiveState = 0;
int8_t tilt = 0;
static bool MagReady = false;
int16_t AccOffset[3] = {232, 30, -1828};
int16_t AccData[3] = {0}, GyroData[3] = {0}, MPU_Temp = 0;
float Roll, Pitch, Yaw, Height, Heading;
static bool settleDown = 0;
static float Init_Altitude, Init_Heading;
Matrix(GyroDCM, 3, 3);
Matrix(AccDCM, 3, 3);
Matrix(MagDCM, 3, 3);
