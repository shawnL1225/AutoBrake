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
    else if (in == '@') digitalWrite(41,1);
    else if (in == '#') digitalWrite(41,0);
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
    }
  }
  
  if (Serial1.available()) {
    char in = Serial1.read();
    if (in == '?') SDWrite("Bluetooth Connected");
    else if (in == '@') {
      digitalWrite(41,1);
      Serial.println('@');
    }
    else if (in == '#') {
      digitalWrite(41,0);
      Serial.println('#');
    }
  }
  if (Serial2.available()){
    char in = Serial2.read();
    String R = 'R';
    if (in == 'R') {
      while (Serial2.available()){
        char a = Serial2.read();
        R += a;
        if (a =='S') {
          Serial1.print("Z1r|");
          R = "";
          break;
        }
      }
      Serial.println(R);
    }
  }
  if (Serial3.available()){
    char in = Serial3.read();
    String L = 'L';
    if (in == 'L') {
      while (Serial2.available()){
        char a = Serial2.read();
        L += a;
        if (a =='L') {
          Serial1.print("Z1l|");
          L = "";
          break;
        }
      }
      Serial.println(L);
    }
  }
  if (Serial4.available()){
    char in = Serial4.read();
    String C = 'C';
    if (in == 'C') {
      while (Serial2.available()){
        char a = Serial2.read();
        C += a;
        if (a =='C') {
          Serial1.print("Z1b|");
          C = "";
          break;
        }
      }
      Serial.println(C);
    }
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
    else if (in == 't'){
      
    }
    else if (in == 'h'){
      
    }
  }
}
