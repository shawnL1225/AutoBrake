void brakeA(){
  if (requestForce-20>TbrakeF&&autoBF<autoBMaxF){
    digitalWrite(5,1);
    while (requestForce>TbrakeF){
      Serial.println("Force bigger");
      brakeS();
      if (TbrakeF>=requestForce||autoBF>=autoBMaxF){
        digitalWrite(5,0);
        break;
      }
    }
    digitalWrite(5,0);
    Serial.println("Force STOP");
  }
  
  else if (requestForce+20<TbrakeF&&autoBF>autoBMinF){
    digitalWrite(6,1);
    while (requestForce<TbrakeF){
      Serial.println("Force Smaller");
      brakeS();
      if (TbrakeF<=requestForce||autoBF<=autoBMinF){
        digitalWrite(6,0);
        break;
      }
    }
    digitalWrite(6,0);
    Serial.println("Force STOP");
  }
  if (autoBF>=autoBMaxF){
    digitalWrite(5,0);
    digitalWrite(6,1);
    delay(100);
    digitalWrite(6,0);
  }
  else if (autoBF<=autoBMinF){
    digitalWrite(6,0);
    digitalWrite(5,1);
    delay(100);
    digitalWrite(5,0);
  }
}
