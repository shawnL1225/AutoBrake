void brakeS(){
  if (brake>brakeMin){
    digitalWrite(24,1);
  }
  
  while (analogRead(2)>orgin){
    Serial.print("H");
    Serial.println(analogRead(2));
    if (analogRead(2)<=orgin){
      digitalWrite(24,0);
      break; 
    }
  }
  
  if (analogRead(2)<=orgin){
      digitalWrite(24,0);
    }
//  */
  while(1){
    int Speed;
    if (Serial2.available()){
      if (Serial2.read()=='V'){
        Speed = Serial2.parseInt();
        Serial.print("H");
        Serial.println(Speed);
    }
    }
    if (Speed<=1||hv<=1) break;
  }
  Serial1.print("S0|");
  hv=0;
  Serial.println("V0");
  delay(10);
  Serial1.print("Z0|");
  
//  /*
  if (analogRead(2)<brake){
    digitalWrite(22,1);  
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
