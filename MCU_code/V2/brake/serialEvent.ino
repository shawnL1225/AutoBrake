void SerialEvent(){
  if (Serial.available()){
    char in = Serial.read();
    if (in == 'E' ){
      requestForce = Serial.parseInt();
      Serial.println("requestForce:");
      Serial.println(requestForce);
      DirectIn = 1;
      brakeA();
    }
    else if (in == 'R'){
      RBlink = Serial.parseInt();
      light();
    }
    else if (in == 'L'){
      LBlink = Serial.parseInt();
      light();
    }
    else if (in == 'B'){
      BLight = Serial.parseInt();
      light();
    }
  }
}
