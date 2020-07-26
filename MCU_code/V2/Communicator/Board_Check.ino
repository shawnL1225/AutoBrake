void boardCheck(){
  Serial.print("!A");
  Serial1.println("AT");
  delay(100);
  char a1 = Serial1.read();
  char b1 = Serial1.read();
  if (a1=='A'&&b1=='T') Serial.print("!B");
  else {
    statusForBluetooth = 'E';
    Serial.print("?B");
    digitalWrite(MP,0);
  }
  if (digitalRead(S2)) Serial.print("!R");
  else Serial.print("?R");
  if (digitalRead(S3)) Serial.print("!L");
  else Serial.print("?L");
  if (digitalRead(S4)) Serial.print("!C");
  else Serial.print("?C");
  if (digitalRead(S5)) Serial.print("!S");
  else Serial.print("?S");
  if (digitalRead(S9)) Serial.print("!P");
  else Serial.print("?P");
  if (digitalRead(S7)) Serial.print("!X");
  else {
    statusForBluetooth = 'E';
    Serial.print("?X");
    digitalWrite(MP,0);
  }
  if (digitalRead(S8)) Serial.print("!T");
  else Serial.print("?T");
  if (digitalRead(S9)) Serial.print("!Z");
  else {
    statusForBluetooth = 'E';
    Serial.print("?Z");
    digitalWrite(MP,0);
  }
  if (digitalRead(S10)) Serial.print("!D");
  else Serial.print("?D");
  if (digitalRead(S11)) Serial.print("!E");
  else Serial.print("?E");
  if (digitalRead(S12)) Serial.print("!N");
  else {
    statusForBluetooth = 'E';
    Serial.print("?N");
    digitalWrite(MP,0);
  }
  if (digitalRead(S13)) Serial.print("!F");
  else Serial.print("?F");
}
