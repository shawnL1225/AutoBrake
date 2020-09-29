void brakeA(){
  if ((requestForce-5 >autoBF||DirectIn == 1)&&autoBF<autoBMaxF){
    digitalWrite(5,1);
    while (autoBF+5>=requestForce||requestForce>autoBF){
      Serial.println("Force bigger");
      brakeS();
      SerialEvent();
      if (autoBF+2>=requestForce||autoBF>=autoBMaxF){
        digitalWrite(5,0);
        break;
      }
    }
    digitalWrite(5,0);
    Serial.println("Force STOP");
    DirectIn = 0;
  }
  
  else if ((requestForce+5<autoBF||DirectIn == 1)&&autoBF>autoBMinF&&autoBF>3){
    digitalWrite(6,1);
    while (autoBF-2<=requestForce|requestForce<autoBF){
      Serial.println("Force Smaller");
      brakeS();
      SerialEvent();
      if (autoBF-5<=requestForce||autoBF<=autoBMinF){
        digitalWrite(6,0);
        break;
      }
    }
    digitalWrite(6,0);
    Serial.println("Force STOP");
    DirectIn = 0;
  }
  if (autoBF-3>=autoBMaxF){
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
