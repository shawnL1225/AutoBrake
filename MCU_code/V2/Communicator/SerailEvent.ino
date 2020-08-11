void SerialEvent(){
//  Serial.println("SEIN");
  if (Serial.available()){
    char in = Serial.read();
    Serial.print(in);
    if (in == 'A'){
      bool requestRader= bool (Serial.parseInt());
      if (requestRader) {
        Serial2.println("A1");
        Serial3.println("A1");
        Serial4.println("A1");
        Serial9.println("A1");
      }
      else {
        Serial2.println("A0");
        Serial3.println("A0");
        Serial4.println("A0");
        Serial9.println("A0");
      }
    }
    else if (in == '@') {
      if (errC==""&&bluetoothStatus=='5') {
        digitalWrite(MP,1);
        Serial2.println('@');
      }
      else {
        Serial.println('#');
        Serial2.println('#');
      }
    }
    else if (in == '#') {
      digitalWrite(MP,0);
      Serial.println('#');
    }
    else if (in == '?') {
      SDWrite("Computer Connected");
      int YYYY = Serial.parseInt();
      int MM = Serial.parseInt();
      int DD = Serial.parseInt();
      int HH = Serial.parseInt();
      int mm = Serial.parseInt();
      int SS = Serial.parseInt();
      rtc.adjust(DateTime(YYYY,MM,DD,HH,mm,SS));   // would set to February 28, 2015 at 14:50:00 (2:50pm)
    }
    else if (in == 'E') {
      int frontBrakeForce = Serial.parseInt();
      Serial9.print("E");
      Serial9.println(frontBrakeForce);
      Serial.println(frontBrakeForce);
    }
    else if (in == 'D') {
      int backBrakeForce = Serial.parseInt();
      Serial9.print("D");
      Serial9.println(backBrakeForce);
    }
    else if (in == 'M') {
      int CTRLP = Serial.parseInt();
      Serial7.print('X');
      Serial7.println(CTRLP);
    }
  }

  if (Serial1.available()) {
    char in = Serial1.read();
//    Serial.println(in);
    if (in == '?') {
      SDWrite("Bluetooth Connected");
      int YYYY = Serial1.parseInt();
      int MM = Serial1.parseInt();
      int DD = Serial1.parseInt();
      int HH = Serial1.parseInt();
      int mm = Serial1.parseInt();
      int SS = Serial1.parseInt();
      rtc.adjust(DateTime(YYYY,MM,DD,HH,mm,SS));   // would set to February 28, 2015 at 14:50:00 (2:50pm)
      String time = ""+String(YYYY)+":"+String(MM)+":"+String(DD)+":"+String(HH)+":"+String(mm)+":"+String(SS);
      Serial.println(time);
      Serial1.print('=');
      bluetoothStatus = 5;
    }
    else if (in == '@') {
      if (errC==""&&bluetoothStatus=='5'){
        digitalWrite(MP,1);
        Serial.println('@');
      }
      else {
        Serial.println('#');
//        Serial2.println('#');
      }
    }
    else if (in == '#') {
      digitalWrite(MP,0);
      Serial.println('#');
    }
    else if (in == '='){
      bluetoothStatus = Serial1.parseInt();
      if (bluetoothStatus!=5) digitalWrite(MP,0);
      else digitalWrite(MP,0);
      Serial.print("W");
      Serial.println(bluetoothStatus);
    }
  }
  
  if (Serial2.available()){
    char in = Serial2.read();
    if (in == 'd'){
      float in1 = Serial2.parseFloat();
      float in2 = Serial2.parseFloat();
      float in3 = Serial2.parseFloat();
      float in4 = Serial2.parseFloat();
      float in5 = Serial2.parseFloat();
      String R ="R "+String(in1)+' '+String(in2)+' '+String(in3)+' '+String(in4)+' '+String(in5) ;
      Serial.println(R);
    }
    else if (in == 'S') {
      Serial1.print("Z1r|");
      S1T = millis();
    }
  }
  
  if (Serial3.available()){
    char in = Serial3.read();
    if (in == 'd'){
      float in1 = Serial3.parseFloat();
      float in2 = Serial3.parseFloat();
      float in3 = Serial3.parseFloat();
      float in4 = Serial3.parseFloat();
      float in5 = Serial3.parseFloat();
      String L ="L "+String(in1)+' '+String(in2)+' '+String(in3)+' '+String(in4)+' '+String(in5) ;
      Serial.println(L);
    }
    else if (in == 'S') {
      Serial1.print("Z1l|");
      S1T = millis();
    }
  }

  Serial4.listen();
  delay(20);
  Serial4.listen();
  if (Serial4.available()){
    char in = Serial4.read();
//    Serial.println(in);
    if (in == 'C'){
      float disB = Serial4.parseFloat();
      String C ="C "+String(disB);
      Serial.println(C);
      if (disB>100) {
        Serial1.print("Z1b|");
        S1T = millis();
      }
    }
    else if (in == 'G'){
      int tiltA = Serial4.parseInt();
      String G = "G" + tiltA ;
      Serial.print(G);
    }
    else if (in == 'I'){
      int RiseA = Serial4.parseInt();
      String I = "I" + RiseA ;
      Serial.print(I);
      Serial9.print(I);
    }
    else if (in == 'A'){
      int Acc = Serial4.parseInt();
      String A = "A" + Acc ;
      Serial.print(A);
    }
    else if (in == 't'){
      int temp = Serial4.parseInt();
      Serial.print("t");
      Serial.println(temp);
    }
  }

  Serial5.listen();
  delay(20);
  Serial5.listen();
  if (Serial5.available()){
    char in = Serial5.read();
//    Serial.println(in);
    if (in == 'V'){
      nowSpeed = Serial5.parseInt();
//      Serial.println(nowSpeed);
      String send = "V" + String(nowSpeed)+' ';
      Serial.println(send);
      Serial1.print('S');
      Serial1.print(nowSpeed);
      Serial1.print('|');
      Serial7.print(send);
      for (int i = 0 ; i<70 ; i++) Serial9.print(send);
    }
  }

  Serial7.listen();
  delay(20);
  Serial7.listen();
  if (Serial7.available()){
    char in = Serial7.read();
    if (in == 'X'){
     int CTRLP = Serial7.parseInt();
     Serial.print('X');
     Serial.print(CTRLP); 
     Serial.print(' ');
    }
    else if (in == '^') ;
    else if (in == 'B') {
      int batteryP = Serial7.parseInt();
      String B = "B" + batteryP;
      Serial.println(B);
      Serial1.print(B);
      Serial1.print('|');
      BP = batteryP;
      if (batteryP<1000) digitalWrite(41,0);
    }
    else if (in =='T'){
      MT = Serial7.parseInt();
      Serial.print('T');
      Serial.println(MT);
    }
  }

  Serial8.listen();
  delay(20);
  Serial8.listen();
  if (Serial8.available()){
    char in = Serial8.read();
  }

  Serial9.listen();
  delay(20);
  Serial9.listen();
  if (Serial9.available()){
    char in = Serial9.read();
    String F = "F";
    if (in == 'E'){
      int frontBrakeForce = Serial9.parseInt();
      Serial.print("E");
      Serial.print(frontBrakeForce);
      Serial.println(' ');
    }
    else if (in == 'D') {
      int backBrakeForce = Serial9.parseInt();
      Serial.print("D");
      Serial.print(backBrakeForce);
      Serial.println(' ');
    }
    else if (in == 'F'){
      if (Serial9.available()){
        char a = Serial9.read();
        F += a;
      }
      Serial.println(F);
    }
  }

  if (millis() - S1T < 1000){
    Serial1.print("Z0|");
    Serial1.print("Y0|");
    Serial1.print("X0|");
  }



  //======SEND======
  Serial6.print('B');
  Serial6.print(BP);
  Serial6.print('T');
  Serial6.print(MT);
  Serial6.print('S');
  Serial6.print(nowSpeed);
//  Serial6.print('E');
//  Serial6.print(errC.length());
//  Serial6.print(errC);
//  Serial.println("SEOUT");
}
