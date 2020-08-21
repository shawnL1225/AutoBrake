void light(){
  if (frontRotateAngle> 8){
    Serial.println("LEFT TURN");
    Serial10.println("R0");
    Serial11.println("R0");
    Serial11.flush();
    Serial10.println("L1");
    Serial11.println("L1");
    Serial11.flush();
  }
  else if (frontRotateAngle< -8){
    Serial.println("RIGHT TURN");
    Serial10.println("L0");
    Serial11.println("L0");
    Serial11.flush();
    Serial10.println("R1");
    Serial11.println("R1");
    Serial11.flush();
  }
  else if (abs(frontRotateAngle) < 5){
    Serial.println("STRAIGHT");
    Serial10.println("L0");
    Serial11.println("L0");
    Serial11.flush();
    Serial10.println("R0");
    Serial11.println("R0");
    Serial11.flush();
  }
}
