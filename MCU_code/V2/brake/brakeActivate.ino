void brakeA(){
  if (requestForce-10>TbrakeF&&autoBF<autoBMaxF){
    digitalWrite(5,1);
    while (requestForce>TbrakeF){
      Serial.println("Force bigger");
      brakeS();
      SerialEvent();
      if (TbrakeF>=requestForce||autoBF>=autoBMaxF){
        digitalWrite(5,0);
        break;
      }
    }
    digitalWrite(5,0);
    Serial.println("Force STOP");
  }
  
  else if (requestForce+10<TbrakeF&&autoBF>autoBMinF){
    digitalWrite(6,1);
    while (requestForce<TbrakeF){
      Serial.println("Force Smaller");
      brakeS();
      SerialEvent();
      if (TbrakeF<=requestForce||autoBF<=autoBMinF){
        digitalWrite(6,0);
        break;
      }
    }
    digitalWrite(6,0);
    Serial.println("Force STOP");
  }
  if (autoBF-5>=autoBMaxF){
    digitalWrite(5,0);
    digitalWrite(6,1);
    delay(100);
    digitalWrite(6,0);
    Serial.println("autoBrake Fixing");
  }
  else if (autoBF+5<=autoBMinF){
    digitalWrite(6,0);
    digitalWrite(5,1);
    delay(100);
    digitalWrite(5,0);
    Serial.println("autoBrake Fixing");
  }
  if (analogRead(A2)>=1000){
    digitalWrite(5,0);
    digitalWrite(6,1);
    delay(100);
    digitalWrite(6,0);
    Serial.println("autoBrake Fixing(S)<F>");
  }
  else if (analogRead(A2)+10<=50){
    digitalWrite(6,0);
    digitalWrite(5,1);
    delay(100);
    digitalWrite(5,0);
    Serial.println("autoBrake Fixing(B)<F>");
  }
}
