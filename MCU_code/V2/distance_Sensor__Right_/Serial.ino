void SerialEvent(){
  if (Serial4.available()){
    char in = Serial4.read();
    if (in == 'A'){
      int inA = Serial4.parseInt();
      if (inA==1) {
        Serial4required=1;
        Serial.println("startSharing");
      }
      else Serial4required=0;
    }
    Serial.print(Serial4required);
  }
}
