void light(){
  if (RBlink||LBlink){
    if (millis()-Btime>300){
      if (!Bstatus){
//        Serial.println("IN");
        if (RBlink) analogWrite(9,50);
        if (LBlink) analogWrite(10,50);
        Bstatus = 1;
      }
      else {
        analogWrite(9,0);
        analogWrite(10,0);
        Bstatus = 0;
      }
      Btime = millis();
    }
  }
  if (BLight) analogWrite(11,50);
  else if (!BLight) analogWrite(11,0);
}
