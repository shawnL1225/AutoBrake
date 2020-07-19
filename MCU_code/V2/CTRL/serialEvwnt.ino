void serialEvent(){
  if (1){
    if (Serial4.available()){
      char in = Serial4.read();
      if (in == 'V') nowSpeed = Serial4.parseInt();
    }
  }
}
