void serialEvent(){
  if (1){
    if (Serial4.available()){
      char in = Serial4.read();
      if (in == '@') {
        appStart = 1;
        Serial.println("Bike UNLOCK");
      }
      else if (in == '%') {
        appStart = 0;
        motor(94, hv, brake);
        Serial.println("Bike LOCK");
      }
    }
  }
}
