void serialEvent() {
  while (Serial.available()) {
      switch(ReceiveState){
          case 0:
              if(Serial.read() == '^')
                  ReceiveState++;
              break;
          case 1:
              switch(Serial.read()){
                  case 'M':
                      ReceiveState++;
                      break;
                  case 'A':
                      ReceiveState = 6;
                      break;
                  defult:
                      ReceiveState = 0;
                      break;
              }
              break;
          case 2:
              t = Serial.read();
              ReceiveState++;
              break;
          case 3:
              x = Serial.read();
              ReceiveState++;
              break;
          case 4:
              y = Serial.read();
              ReceiveState++;
              break;
          case 5:
              if(Serial.read() == 'E')
              {
                  Throttle = t;
//                  x_Axis = x;
//                  y_Axis = y;
                  ReceiveDone = true;
              }
              ReceiveState = 0;
              break;
          case 6:
              m = Serial.read();
              ReceiveState++;
              break;
          case 7:
              a = Serial.read();
              ReceiveState++;
              break;
          case 8:
              if(Serial.read() == 'E')
              {
                  if(m == 1)
                      x_Axis = a;
                  else if(m == 2)
                      y_Axis = a;
                  AdjustDone = true;
              }
              ReceiveState = 0;
              break;           
      }
  }
}
