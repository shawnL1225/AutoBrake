void SerialEvent(){
  if (Serial.available()){
    char in = Serial.read();
    if (in == '@') {
      motorper = 1;
      digitalWrite(25,1);
      Serial.println('@');
    }
    else if (in == '#') {
      motorper = 0;
      digitalWrite(25,0);
      Serial.println('#');
    }
  }
  if (Serial1.available()){
    char in = Serial1.read();
    Serial.print(in);
    if (in == '?'){
      Serial1.print('=');
      Serial.println("=");
      delay(100);
      Serial1.print("B90|");
      delay(100);
    }
    else if (in == '@') {
      motorper = 1;
      digitalWrite(25,1);
      Serial.println('@');
    }
    else if (in == '#') {
      motorper = 0;
      digitalWrite(25,0);
      Serial.println('#');
    }
  }
  if (Serial2.available()){
    char in = Serial2.read();
    if (in == 'V'){
      nowSpeed = Serial2.parseInt();
      String send = 'S' + String(nowSpeed/100)+'|';
      Serial.println(send);
      Serial1.print(send);
      delay(25);
      Serial1.println("B90|");
      Serial.println("B90|");
    }
  }
}
