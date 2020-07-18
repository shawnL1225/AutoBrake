void serialEvent(){
  if (1){
    if (Serial4.available()){
      char in = Serial4.read();
      if (in == '@') {
        digitalWrite(7,0);
        Serial.println("Bike UNLOCK");
      }
      else if (in == '%') {
        digitalWrite(7,1);
        Serial.println("Bike LOCK");
      }
      
      if (in == 'V') nowSpeed = Serial4.parseInt();
    }
  }
}
