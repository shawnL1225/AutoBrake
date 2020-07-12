void ultra(){
  digitalWrite(ultraLTP,0);
  digitalWrite(ultraMTP,0);
  digitalWrite(ultraRTP,0);
  delay(2);
  digitalWrite(ultraLTP,1);
  digitalWrite(ultraMTP,1);
  digitalWrite(ultraRTP,1);
  delay(10);
  digitalWrite(ultraLTP,0);
  digitalWrite(ultraMTP,0);
  digitalWrite(ultraRTP,0);
  
  long Lduration = pulseIn(ultraLEP, HIGH);
  long Mduration = pulseIn(ultraMEP, HIGH);
  long Rduration = pulseIn(ultraREP, HIGH);
  
  ultraLD = Lduration/58.0;
  ultraMD = Mduration/58.0;
  ultraMD-=3.1;
  ultraRD = Rduration/58.0;
}
