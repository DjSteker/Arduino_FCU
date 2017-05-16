void OutputData(){
  if(settleDown){
    if(!MagReady && !digitalRead(Button_Pin))
    {
      MagReady = true;
      eye_Matrix(GyroDCM, 3);
      Init_Heading = Heading;
      Serial.println("Yaw is Ready!!");
    }
    mat2ang(GyroDCM, &Roll, &Pitch, &Yaw);
    tilt = int8_t(Pitch);
    uint8_t DataToSend[20];
    AttitudePackage(DataToSend, Roll, Pitch, Yaw, Height);
//    Serial.write(DataToSend, 20);
//    Serial.print("Roll: ");Serial.print(Roll);Serial.print(" ");
//    Serial.print("Pitch: ");Serial.print(Pitch);Serial.print(" ");
//    Serial.print("Yaw: ");Serial.print(Yaw);Serial.print(" ");
//    Serial.print("Height: ");Serial.println(Height);
  }
}
