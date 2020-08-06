void boardCheck(){
  Serial.println("!A");
  Serial1.println("AT");
  Serial2.println("?");
  Serial3.println("?");
  Serial4.println("?");
  Serial5.println("?");
  Serial6.println("?");
  Serial7.println("?");
  Serial8.println("?");
  Serial9.println("?");
  delay(100);
  
  while(!Serial1.available());
  char in1 = Serial1.read();
  if (in1=='O') Serial.println("!T");
  else {
    errC = errC+'T';
    Serial.println("?T");
    digitalWrite(MP,0);
    statusForBluetooth = 'E' ; 
  }
  
  while(!Serial2.available());
  char in2 = Serial2.read();
  if (in2=='O') Serial.println("!R");
  else {
    errC = errC+'R';
    Serial.println("?R");
  }
  
  while(!Serial3.available());
  char in3 = Serial3.read();
  if (in3=='O') Serial.println("!L");
  else {
    errC = errC+'L';
    Serial.println("?L");
  }

  while(!Serial4.available());
  char in4 = Serial4.read();
  if (in4=='O') Serial.println("!C");
  else {
    errC = errC+'C';
    Serial.println("?C");
  }

  while(!Serial5.available());
  char in5 = Serial5.read();
  if (in5=='O') Serial.println("!S");
  else {
    errC = errC+'S';
    Serial.println("?S");
  }

  while(!Serial6.available());
  char in6 = Serial6.read();
  if (in6=='O') Serial.println("!P");
  else {
    errC = errC+'P';
    Serial.println("?P");
  }
  
  while(!Serial7.available());
  char in7 = Serial7.read();
  if (in7=='O') Serial.println("!X");
  else {
    errC = errC+'X';
    Serial.println("?X");
    digitalWrite(MP,0);
    statusForBluetooth = 'E' ; 
  }

  while(!Serial8.available());
  char in8 = Serial8.read();
  if (in8=='O') Serial.println("!T");
  else {
    errC = errC+'T';
    Serial.println("?T");
  }

  while(!Serial9.available());
  char in9 = Serial9.read();
  if (in9=='O') {
    Serial.println("!Z");
    Serial.println("!D");
    Serial.println("!E");
    Serial.println("!N");
    Serial.println("!F");
  }
  else {
    errC = errC+'Z';
    Serial.println("?Z");
    digitalWrite(MP,0);
    statusForBluetooth = 'E' ; 
  }
}
