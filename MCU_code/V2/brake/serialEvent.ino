void SerialEvent(){
  if (Serial.available()){
    char in = Serial.read();
    if (in == 'E' ){
      requestForce = Serial.parseInt();
      Serial.println("requestForce:");
      Serial.println(requestForce);
    }
  }
  if (Serial4.available()){
    char in = Serial4.read();
    if (in == 'E' ){
      requestForce = Serial4.parseInt();
      Serial.println("requestForce:");
      Serial.println(requestForce);
    }
  }
}
