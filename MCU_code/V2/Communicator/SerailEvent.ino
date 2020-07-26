void SerialEvent(){
  if (Serial.available()){
    char in = Serial.read();
    if (in == 'A'){
      bool requestRader= bool (Serial.parseInt());
      if (requestRader) {
        Serial2.print("A1");
        Serial3.print("A1");
        Serial4.print("A1");
        Serial9.print("A1");
      }
      else {
        Serial2.print("A0");
        Serial3.print("A0");
        Serial4.print("A0");
        Serial9.print("A0");
      }
    }
    else if (in == '@') {
      if (statusForBluetooth==""&&bluetoothStatus=='6') {
        digitalWrite(MP,1);
        Serial2.print('@');
      }
      else {
        Serial.println('#');
        Serial2.print('#');
      }
    }
    else if (in == '#') {
      digitalWrite(MP,0);
      Serial.print('#');
    }
    else if (in == '?') SDWrite("Computer Connected");
    else if (in == 'E') {
      int frontBrakeForce = Serial.parseInt();
      Serial9.print("E");
      Serial9.print(frontBrakeForce);
      Serial9.print(' ');
      
    }
    else if (in == 'D') {
      int backBrakeForce = Serial.parseInt();
      Serial9.print("D");
      Serial9.print(backBrakeForce);
      Serial9.print(' ');
    }
    else if (in == 'M') {
      int CTRLP = Serial.parseInt();
      Serial7.print('X');
      Serial7.print(CTRLP);
      Serial7.print(' ');
    }
  }
  
  if (Serial1.available()) {
    char in = Serial1.read();
    if (in == '?') SDWrite("Bluetooth Connected");
    else if (in == '@') {
      if (statusForBluetooth==""&&bluetoothStatus=='6'){
        digitalWrite(MP,1);
        Serial.println('@');
      }
      else {
        Serial.println('#');
        Serial2.print('#');
      }
    }
    else if (in == '#') {
      digitalWrite(MP,0);
      Serial.println('#');
    }
  }
  String R ="";
  while (Serial2.available()){
    char in = Serial2.read();
    R += in ;
    if (in == '^') {
      Serial.println(R);
      R = "";
    }
    else if (in == 'S') Serial1.print("Z1r|");
  }
  
  String L = "";
  while (Serial3.available()){
    char in = Serial3.read();
    L += in ;
    if (in == '^') {
      Serial.println(L);
      L = "";
    }
    else if (in == 'S') Serial1.print("Z1l|");
  }
  String C = "" ;
  while (Serial4.available()){
    char in = Serial4.read();
    C += in ;
    if (in == '^') {
      Serial.println(C);
      C = "";
    }
    else if (in == 'S') Serial1.print("Z1b|");
  }
  
  if (Serial5.available()){
    char in = Serial5.read();
    String F = "F" ;
    if (in == 'V'){
      int nowSpeed = Serial5.parseInt();
      SP = nowSpeed;
      String send = "V" + nowSpeed ;
      Serial.println(send);
      Serial1.print('S');
      Serial1.print(nowSpeed);
      Serial7.print(send);
      Serial9.print(send);
    }
  }
  if (Serial9.available()){
    char in = Serial9.read();
    String F = "F";
    if (in == 'E'){
      int frontBrakeForce = Serial.parseInt();
      Serial.print("E");
      Serial.print(frontBrakeForce);
      Serial.println(' ');
    }
    else if (in == 'D') {
      int backBrakeForce = Serial.parseInt();
      Serial.print("D");
      Serial.print(backBrakeForce);
      Serial.println(' ');
    }
    else if (in == 'F'){
      while (Serial9.available()){
        char a = Serial9.read();
        F += a;
      }
      Serial.println(F);
    }
  }
  if (Serial7.available()){
    char in = Serial7.read();
    if (in == 'X'){
     int CTRLP = Serial7.parseInt();
     Serial.print('X');
     Serial.print(CTRLP); 
     Serial.print(' ');
     Serial1.print('M');
     Serial1.print(CTRLP);
     Serial1.print(' ');
    }
    else if (in == '^') ;
    else if (in == 'B') {
      int batteryP = Serial7.parseInt();
      String B = "B" + batteryP;
      Serial.println(B);
      Serial1.println(B);
      BP = batteryP;
      if (batteryP<1000) digitalWrite(41,0);
    }
  }
  if (Serial8.available()){
    char in = Serial8.read();
    if (in == 'G'){
      int tiltA = Serial8.parseInt();
      String G = "G" + tiltA ;
      Serial.print(G);
    }
    else if (in == 'I'){
      int RiseA = Serial8.parseInt();
      String I = "I" + RiseA ;
      Serial.print(I);
      Serial9.print(I);
    }
    else if (in == 'A'){
      int Acc = Serial8.parseInt();
      String A = "A" + Acc ;
      Serial.print(A);
    }
    else if (in == 'T'){
      int motorTemp = Serial8.parseInt();
      String send = "T" + motorTemp;
      Serial.print(send);
      Serial1.print(send);
      MT = motorTemp;
    }
    else if (in == 't'){
      
    }
    else if (in == 'h'){
      
    }
  }
}
