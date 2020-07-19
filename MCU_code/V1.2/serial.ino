void SerialEvent(){
  if (Serial1.available()){
    char in = Serial1.read();
    if (in == '?'){
      Serial1.print('=');
    }
    else if (in == '@') {
      motorper = 1;
      digitalWrite(31,0);
    }
    else if (in == '#') {
      motorper = 0;
      digitalWrite(31,0);
    }
  }
  if (Serial2.available()){
    char in = Serial2.read();
    if (in == 'V'){
      nowSpeed = Serial2.parseInt();
      Serial1.print(nowSpeed);
    }
  }
}
