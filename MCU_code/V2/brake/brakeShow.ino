void brakeA(int requestForce){
  if (requestForce>TbrakeF){
    digitalWrite(6,1);
  }
  
  while (requestForce>TbrakeF){
    brakeS();
    if (TbrakeF>requestForce){
      digitalWrite(6,0);
      break;
    }
  }
  
  if (TbrakeF>requestForce){
    digitalWrite(6,0);
  }

  while(requestForce != 0){
    if (Serial4.available()){
      if (Serial4.read()=='E'){
        int requestForce = Serial4.parseInt();
      }
    }
    if (requestForce == 0) break;
  }

  if ((TbrakeF-manualBF)>autoBFMax){
    digitalWrite(5,1);
  }
  
  while (analogRead(2)<brake){
    Serial.print("H");
    Serial.println(analogRead(2));
    if (analogRead(2)>=brake){
      digitalWrite(22,0);
      break;
    }
  }
  if (analogRead(2)>=brake){
    digitalWrite(22,0);
  }
}
