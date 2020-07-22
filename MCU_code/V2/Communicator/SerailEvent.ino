void SerialEvent(){
  if (Serial.available()){
    char in = Serial.read();
    if (in == 'A'){
      bool requestRader= bool (Serial.parseInt());
      if (requestRader) {
        Serial2.print("A1");
        Serial3.print("A1");
        Serial4.print("A1");
        Serial6.print("A1");
      }
      else {
        Serial2.print("A0");
        Serial3.print("A0");
        Serial4.print("A0");
        Serial6.print("A0");
      }
    }
    else if (in == '@') digitalWrite(33,1);
    else if (in == '#') digitalWrite(33,0);
    else if (in == '?') SDWrite("Computer Connected");
    else if (in == 'E') {
      frontBrakeForce = Serial.parseInt();
      Serial6.print("E");
      Serial6.print(frontBrakeForce);
      Serial6.print(' ');
    }
    else if (in == 'D') {
      backBrakeForce = Serial.parseInt();
      Serial6.print("D");
      Serial6.print(backBrakeForce);
      Serial6.print(' ');
    }
    else if (in == 'M') {
      CTRLP = Serial.parseInt();
      Serial7.print('X');
      Serial7.print(CTRLP);
      Serial7.print(' ');
    }
  }
  
  if (Serial1.available()) {
    char in = Serial1.read();
    if (in == '?') SDWrite("Bluetooth Connected");
    else if (in == '@') {
      digitalWrite(33,1);
      Serial.println('@');
    }
    else if (in == '#') {
      digitalWrite(33,0);
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
    String F = 'F' ;
    if (in == 'V'){
      int nowSpeed = Serial5.parseInt();
      String send = 'V' + nowSpeed ;
      Serial.println(send);
      Serial1.print('S');
      Serial1.print(nowSpeed);
      Serial6.print(send);
      Serial7.print(send);
    }
  }
  if (Serial6.available()){
    char in = Serial6.read();
    if (in == 'E'){
      frontBrakeForce = Serial.parseInt();
      Serial.print("E");
      Serial.print(frontBrakeForce);
      Serial.println(' ');
    }
    else if (in == 'D') {
      backBrakeForce = Serial.parseInt();
      Serial.print("D");
      Serial.print(backBrakeForce);
      Serial.println(' ');
    }
    else if (in == 'F'){
      while (Serial6.available()){
        char a = Serial6.read();
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
      int bateryP = parseInt();
      String send = 'B' + batteryP;
      Serial.println(B);
      Serial1.println(B);
      if (batteyP<1000) digitalWrite(41,0);
    }
  }
  if (Serial8.available()){
    char in = Serial8.read();
    if (in == 'G'){
      int tiltA = Serial8.parseInt();
      String G = 'G' + tiltA ;
      Serial.print(G);
    }
    else if (in == 'I'){
      int RiseA = Serial8.parseInt();
      String I = 'I' + RiseA ;
      Serial.print(I);
      Serial6.print(I);
    }
    else if (in == 'A'){
      int Acc = Serial8.parseInt();
      String A = 'A' + Acc ;
      Serial.print(A);
    }
    else if (in == 'T'){
      int motorTemp = Serial8.parseInt();
      String send = 'T' + motorTemp;
      Serial.print(send);
      Serial1.print(send);
    }
    else if (in == 't'){
      
    }
    else if (in == 'h'){
      
    }
  }
}
