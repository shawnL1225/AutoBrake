void SerialEvent(){
  if (Serial4.available()){
    char in = Serial4.read();
    if (in == 'E' ){
      int requestForce = Serial4.parseInt();
      brakeA(requestForce);
    }
  }
}
