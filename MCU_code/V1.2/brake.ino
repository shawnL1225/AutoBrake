void brake(){
  int brake=690, orgin=920;
  Serial.print("BrakeActivate");
  Serial1.print("Z1f|");
  Serial.println("HZ|");
  digitalWrite(24,1);
  delay(1500);
  digitalWrite(24,0);

  /*
  if (analogRead(2)>orgin){
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
  
  while(1){
    int Speed;
    if (Serial2.available()){
      if (Serial2.read()=='V'){
        Speed = Serial2.parseInt();
        Serial.print("H");
        Serial.println(Speed);
      }
    }
    if (Speed<=1||nowSpeed<=1) break;
  }*/
  delay(3000);
  Serial1.print("S0|");
  nowSpeed=0;
  Serial.println("V0");
  delay(10);
  Serial1.print("Z0|");
  
  /*
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
  
  */

  digitalWrite(22,1);
  delay(1400);
  digitalWrite(22,0);
  delay(10);
  digitalWrite(31,1);
}
