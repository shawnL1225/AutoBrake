void boardCheck(){
  Serial.println("!A");
  Serial1.println("AT");
  delay(100);
  char a1 = Serial1.read();
  char b1 = Serial1.read();
  if (a1=='A'&&b1=='T') Serial.println("!B");
  else {
    statusForBluetooth = 'E';
    Serial.println("?B");
    digitalWrite(MP,0);
  }
  if (digitalRead(S2)) Serial.println("!R");
  else Serial.println("?R");
  if (digitalRead(S3)) Serial.println("!L");
  else Serial.println("?L");
  if (digitalRead(S4)) Serial.println("!C");
  else Serial.println("?C");
  if (digitalRead(S5)) Serial.println("!S");
  else Serial.println("?S");
  if (digitalRead(S9)) Serial.println("!P");
  else Serial.println("?P");
  if (digitalRead(S7)) Serial.println("!X");
  else {
    statusForBluetooth = 'E';
    Serial.println("?X");
    digitalWrite(MP,0);
  }
  if (digitalRead(S8)) Serial.println("!T");
  else Serial.println("?T");
  if (digitalRead(S9)) Serial.println("!Z");
  else {
    statusForBluetooth = 'E';
    Serial.println("?Z");
    digitalWrite(MP,0);
  }
  if (digitalRead(S10)) Serial.println("!D");
  else Serial.println("?D");
  if (digitalRead(S11)) Serial.println("!E");
  else Serial.println("?E");
  if (digitalRead(S12)) Serial.println("!N");
  else {
    statusForBluetooth = 'E';
    Serial.println("?N");
    digitalWrite(MP,0);
  }
  if (digitalRead(S13)) Serial.println("!F");
  else Serial.println("?F");
}
