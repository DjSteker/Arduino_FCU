void setup() {
  pinMode(Button_Pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); pinMode(RF_MD0, OUTPUT); pinMode(RF_MD1, OUTPUT);
  eye_Matrix(GyroDCM, 3); eye_Matrix(AccDCM, 3); eye_Matrix(MagDCM, 3);
  Left_Servo.attach(5); Right_Servo.attach(6); Left_Motor.attach(3); Right_Motor.attach(9);
  Left_Motor.writeMicroseconds(map(Throttle, 0, 180, 900, 2000)); Right_Motor.writeMicroseconds(map(Throttle, 0, 180, 900, 2000));
  Left_Servo.writeMicroseconds(map(x_Axis, 0, 180, 1000, 2000)); Right_Servo.writeMicroseconds(map(y_Axis, 0, 180, 1000, 2000));
  Serial.begin(9600);
  delay(1000);
  Wire.begin();
  BMP180_Init();
  Init_Altitude = BMP180_GetAltitude();
  MPU6050_Init();
  MPU6050_I2C_Bypass(true);
  HMC5883L_Init();
  digitalWrite(RF_MD0, LOW); digitalWrite(RF_MD1, LOW); digitalWrite(LED_BUILTIN, HIGH);
  settleDown = 1;
}
