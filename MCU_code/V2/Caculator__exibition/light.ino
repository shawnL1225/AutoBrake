void light(){
  if (abs(frontRotateAngle)>30) Serial.println("GYRO ERR");
  else if (frontRotateAngle> 8&&!LS){
    Serial.println("LEFT TURN");
    Serial10.println("R0");
    Serial11.println("R0");
    Serial11.flush();
    Serial10.println("L1");
    Serial11.println("L1");
    Serial11.flush();
    LS = 1;
    RS = 0;
    FS = 0;
  }
  else if (frontRotateAngle< -8&&!RS){
    Serial.println("RIGHT TURN");
    Serial10.println("L0");
    Serial11.println("L0");
    Serial11.flush();
    Serial10.println("R1");
    Serial11.println("R1");
    Serial11.flush();
    LS = 0;
    RS = 1;
    FS = 0;
  }
  else if (abs(frontRotateAngle) < 5&&!FS){
    Serial.println("STRAIGHT");
    Serial10.println("L0");
    Serial11.println("L0");
    Serial11.flush();
    Serial10.println("R0");
    Serial11.println("R0");
    Serial11.flush();
    LS = 0;
    RS = 0;
    FS = 1;
  }
}
