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
  
  ultraLD = Lduration/soundSpeed;
  if (ultraLD<50) {
    BultraLD = 1 ;
    trigger_time  = millis();;
  }
  else if (trigger_time - millis()<5000) BultraLD = 0 ;
  
  ultraMD = Mduration/soundSpeed;
  ultraMD-=3.1;
  if (ultraMD<50) {
    BultraMD = 1 ;
    trigger_time  = millis();
  }
  else if (trigger_time - millis()<2000) BultraMD = 0 ;
  
  ultraRD = Rduration/soundSpeed;
  if (ultraRD<50) {
    BultraRD = 1 ;
    trigger_time  = millis();
  }
  else if (trigger_time - millis()<5000) BultraRD = 0 ;
  
}
