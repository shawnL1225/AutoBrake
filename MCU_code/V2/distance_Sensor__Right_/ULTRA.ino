void ultra(){
  digitalWrite(ultraLTP,0);
  delay(2);
  digitalWrite(ultraLTP,1);
  delay(10);
  digitalWrite(ultraLTP,0);
  long Lduration = pulseIn(ultraLEP, HIGH);
  
  digitalWrite(ultraMTP,0);
  delay(2);
  digitalWrite(ultraMTP,1);
  delay(10);
  digitalWrite(ultraMTP,0);
  long Mduration = pulseIn(ultraMEP, HIGH);
  
  digitalWrite(ultraRTP,0);
  delay(2);
  digitalWrite(ultraRTP,1);
  delay(10);
  digitalWrite(ultraRTP,0);
  long Rduration = pulseIn(ultraREP, HIGH);
  
  ultraLD = Lduration/soundSpeed;
  if (ultraLD<50) {
    BultraLD = 1 ;
    ultrigger_time  = millis();;
  }
  else if (millis()-ultrigger_time <5000) BultraLD = 0 ;
  
  ultraMD = Mduration/soundSpeed;
  ultraMD-=3.1;
  if (ultraMD<50) {
    BultraMD = 1 ;
    umtrigger_time  = millis();
  }
  else if (millis()-umtrigger_time <2000) BultraMD = 0 ;
  
  ultraRD = Rduration/soundSpeed;
  if (ultraRD<50) {
    BultraRD = 1 ;
    urtrigger_time  = millis();
  }
  else if (millis()-urtrigger_time <5000) BultraRD = 0 ;
  
}
