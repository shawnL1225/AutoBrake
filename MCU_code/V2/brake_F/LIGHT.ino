void light(){
  if (RBlink||LBlink){
    if (millis()-Btime>300){
      if (!Bstatus){
//        Serial.println("IN");
        if (RBlink) analogWrite(9,50);
        if (LBlink) analogWrite(11,50);
        Bstatus = 1;
      }
      else {
        analogWrite(9,0);
        analogWrite(11,0);
        Bstatus = 0;
      }
      Btime = millis();
    }
  }
  else {
    analogWrite(9,0);
    analogWrite(11,0);
    Bstatus = 0;
  }
}
