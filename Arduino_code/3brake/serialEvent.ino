void serialEvent(){
  bool brake=0;
  if (1){ //sending Envent
    Serial4.write("@");
    if (digitalRead(2)) Serial4.write('1');
    else Serial4.write('0');
    Serial4.write(" ");
    String b = String(brake);
    Serial4.print(b);
  }
  //receive Event
  if (1){
    if(Serial4.available()) {
      if('@' == Serial4.read()) { 
          int n = Serial4.parseInt();
          bool isConnect = bool(n);
          digitalWrite(VGALED,isConnect);
          Serial.println(isConnect);
          int BreakAmount = Serial4.parseInt();
          Serial.println(BreakAmount);
          S1.write(BreakAmount);
          S2.write(BreakAmount);
      }
    }
  }
}
