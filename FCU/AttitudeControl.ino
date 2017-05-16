void AttitudeControl(){
  if (ReceiveDone) {
    Left_Motor.writeMicroseconds(map(Throttle, 0, 180, 1000, 2000));
    Right_Motor.writeMicroseconds(map(Throttle, 0, 180, 1000, 2000));
//    Left_Servo.write(x_Axis);
//    Right_Servo.write(y_Axis);
    ReceiveDone = false;
  }
  if(AdjustDone){
    Left_Servo.writeMicroseconds(map(x_Axis, 0, 180, 1000, 2000));
    Right_Servo.writeMicroseconds(map(y_Axis, 0, 180, 1000, 2000));
    AdjustDone = false;    
  }
}
