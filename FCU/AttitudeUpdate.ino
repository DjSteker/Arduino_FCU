void AttitudeUpdate(){
  const float dt = 0.022f, filter = 0.97, filter2 = 0.96;
  float omega[3], gravity[3], temp_pitch, temp_roll;

  if(settleDown){
    for(int i=0;i<3;i++)
    {
      omega[i] = (float)GyroData[i] * 250.0 / 32768.0;
      gravity[i] = (float)AccData[i] * 2.0 / 32768.0;
    }
    gyroRot(GyroDCM, omega[0] * dt, omega[1] * -dt, omega[2] * -dt);

    temp_pitch = atan2(gravity[0],sqrt(gravity[1]*gravity[1] + gravity[2]*gravity[2])) * 180.0 / M_PI;
    if(gravity[2] > 0)
      temp_roll = atan2(-1.0f * gravity[1], sqrt(gravity[2]*gravity[2] + 0.1f * gravity[0]*gravity[0])) * 180.0 / M_PI;
    else
      temp_roll = atan2(-1.0f * gravity[1], -1.0f * sqrt(gravity[2]*gravity[2] + 0.01f * gravity[0]*gravity[0])) * 180.0 / M_PI;

    eulRot(AccDCM, -temp_roll, temp_pitch, Yaw);

    for(int i=0;i<9;i++)
      GyroDCM[i] = GyroDCM[i] * filter + AccDCM[i] * (1 - filter);
    
    if(MagReady)
    {
      int16_t temp = Heading - Init_Heading;
      if(temp < 0)
        temp += 360;
      if(temp > 180)
        temp -= 360;
      eulRot(MagDCM, Roll, Pitch, temp);
      for(int i=0;i<9;i++)
        GyroDCM[i] = GyroDCM[i] * filter2 + MagDCM[i] * (1 - filter2);
    }
    
  }
}
