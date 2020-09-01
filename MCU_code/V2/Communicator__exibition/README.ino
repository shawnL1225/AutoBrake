// -------------------------PORTS----------------------------------------
  //digital Ports
    
    // D12 -> SD CS port
    // D14-19 -> Serial ports
    // D22-42 -> Serial ports & status ports
   //-===ststus ports===-
    // D36 -> motor permission to CTRL digital Pin 12
    // D22 -> distance sensor [R]
    // D23 -> distance sensor [L]
    // D26 -> distance sensor [B]
    // D29 -> speed sensor
    // D42 -> ESP
    // D35 -> CTRL
    // D39 -> heat n Gsensor
    // D42 -> caculation board
    // D43 -> Brake [F]
    // D45 -> Brake [B]
    // D47 -> Xavier
    // D49 -> distance [F]
    // D50-53 -> SPI
  
  //Communication
/**/// -----=========Serial (deskopSite)======---------
    // --Code symbol for Serial (O)--
      //'?' + charOfMCU -> status
      //'@' -> Enable
      //'#' -> Disable
      //'X' + CTRLP 
      //'V' + nowSpeed 
      //'T' + motorTemp 
      //'G' + tiltAngle
      //'I' + riseAngle
      //'A' + vichileAcc
      //'B' + BatteryP
      //'E' + frontBrakeForce
      //'D' + backBrakeForce
      //'H' + motherBoardSerial
      //'N' + NXTSerial
      //'F' + F_1 + F_2 + F_3
      //'L' + L_1 + L_2 + L_3 + L_4 + L_5
      //'R' + R_1 + R_2 + R_3 + R_4 + R_5
      //'C' + C_1 + C_2 + C_3 
    // --Code symbol for Serial (I)--
      //'@' -> Enable
      //'#' -> Disable
      //'M' + CTRLP
      //'A' + '1/0' -> 1>>require distance
      //'?' -> request for now status
      //"$C" -> connected
      //"$D" -> disconnected
      //'E' + frontBrakeForce
      //'D' + backBrakeForce
      //'H' + mother board Serial
      //'N' + NXT board Serial
      
    // -----=========Serial1 (bluetooth)======---------
    // --Code symbol for Serial1 (I)--
      //'?' -> request for now status
      //'@' -> motor permited
      //'#' -> motor not permited
    // --Code symbol for Serial1 (O)--
      //'S' + speed 
      //'B' + batteryPercentage
      //'X' -> Red Light warning 
      //'Y' -> vechile devious
      //'Z' + '1/0' + 'f/r/l/b' -> distance under limited 
     //----------===== start status =====---------
      //'=' -> System All Set
      //"E" -> Error


    // -----=========Serial2 (distance [R]<R>)|22|======---------
    // --Code symbol for Serial2 (I)--
      //'R' -> ultraRD + IRD80_1 + ultraMD + IRD80_2 + ultraLD
      // RS -> Right side has car
    // --Code symbol for Serial2 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

    // -----=========Serial3 (distance [L]<L>)|23|======---------
    // --Code symbol for Serial3 (I)--
      //'L' -> ultraLD + IRD80_2 + ultraMD + IRD80_1 + ultraRD
      // LS -> Left side has car
    // --Code symbol for Serial3 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

/**/// -----=========Serial4 (distance [B]<C>)|26|======---------
    // --Code symbol for Serial4 (I)--
      //'C' -> ultraLD + IRD80_2 + ultraMD + IRD80_1 + ultraRD
      // CS -> Left side has car
    // --Code symbol for Serial4 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

    // -----=========Serial5 (SpeedSensor <S>)|29|======---------
    // --Code symbol for Serial5 (I)--
      //'V' + hv
      //'E' <Error Occur>
    // --Code symbol for Serial5 (O)--

    // -----=========Serial6 (ESP <P>)|32|======---------
    // --Code symbol for Serial6 (I)--
    // --Code symbol for Serial6 (O)--
      //'B'+batteryV+'T'+temperature+'S'+speed+'E'+errorCode

    // -----=========Serial7 (CTRL <X>)|35|======---------
    // --Code symbol for Serial7 (I)--
      //'X' + CTRLP
      //'^' -> Button Pressed
      //'B' + batteryV <Actual Voltage *100>
    // --Code symbol for Serial7 (O)--
      //'V' + nowSpeed 
      //'X' + CTRLP
    //digitalPin 
      //D41 -> motor permission

    // -----=========Serial8 (Heat n Gsensor <T>)|39|======---------
    // --Code symbol for Serial8 (I)--
      //'G' -> Tilt Angle
      //'I' -> Rise Angle
      //'A' -> acceleratiom
      //'T' -> motor temperatrue
      //'t' -> Temperature for sound
      //'h' -> Humidity for sound
    // --Code symbol for Serial8 (O)--


    // -----=========Serial9 (Caculation <Z>)|42|======---------
    // --Code symbol for Serial9 (I)--
      //'E' + frontBrakeForce
      //'D' + backBrakeForce
      //'F' + F_1 + F_2 + F_3
    // --Code symbol for Serial9 (O)--
      //'A' + '1/0' -> 1 is front distance is required / 0 is not required
      //'I' + riseAngle
      //'V' + nowSpeed
      //'E' + frontBrakeForce
      //'D' + backBrakeForce





//SerialEvent code
//
//void SerialEvent(){
////  Serial.println("SEIN");
//  if (Serial.available()){
//    char in = Serial.read();
//    Serial.print(in);
//    if (in == 'A'){
//      bool requestRader= bool (Serial.parseInt());
//      if (requestRader) {
////        Serial2.println("A1");
////        Serial3.println("A1");
//        Serial4.println("A1");
//        Serial2.println("A1");
//      }
//      else {
////        Serial2.println("A0");
////        Serial3.println("A0");
//        Serial4.println("A0");
//        Serial2.println("A0");
//      }
//    }
//    else if (in == '@') {
//      if (errC==""&&bluetoothStatus=='5') {
//        digitalWrite(MP,1);
//        Serial2.println('@');
//      }
//      else {
//        Serial.println('#');
//        Serial2.println('#');
//      }
//    }
//    else if (in == '#') {
//      digitalWrite(MP,0);
//      Serial.println('#');
//    }
//    else if (in == '?') {
//      SDWrite("Computer Connected");
//      int YYYY = Serial.parseInt();
//      int MM = Serial.parseInt();
//      int DD = Serial.parseInt();
//      int HH = Serial.parseInt();
//      int mm = Serial.parseInt();
//      int SS = Serial.parseInt();
//      rtc.adjust(DateTime(YYYY,MM,DD,HH,mm,SS));   // would set to February 28, 2015 at 14:50:00 (2:50pm)
//    }
//    else if (in == 'E') {
//      int frontBrakeForce = Serial.parseInt();
//      Serial2.print("E");
//      Serial2.println(frontBrakeForce);
//      Serial.println(frontBrakeForce);
//    }
//    else if (in == 'D') {
//      int backBrakeForce = Serial.parseInt();
//      Serial2.print("D");
//      Serial2.println(backBrakeForce);
//    }
//    else if (in == 'M') {
//      int CTRLP = Serial.parseInt();
//      Serial7.print('X');
//      Serial7.println(CTRLP);
//    }
//  }
//
//  if (Serial1.available()) {
//    char in = Serial1.read();
////    Serial.println(in);
//    if (in == '?') {
//      SDWrite("Bluetooth Connected");
//      int YYYY = Serial1.parseInt();
//      int MM = Serial1.parseInt();
//      int DD = Serial1.parseInt();
//      int HH = Serial1.parseInt();
//      int mm = Serial1.parseInt();
//      int SS = Serial1.parseInt();
//      rtc.adjust(DateTime(YYYY,MM,DD,HH,mm,SS));   // would set to February 28, 2015 at 14:50:00 (2:50pm)
//      String time = ""+String(YYYY)+":"+String(MM)+":"+String(DD)+":"+String(HH)+":"+String(mm)+":"+String(SS);
//      Serial.println(time);
//      Serial1.print('=');
//      bluetoothStatus = 5;
//    }
//    else if (in == '@') {
//      if (errC==""&&bluetoothStatus=='5'){
//        digitalWrite(MP,1);
//        Serial.println('@');
//      }
//      else {
//        Serial.println('#');
////        Serial2.println('#');
//      }
//    }
//    else if (in == '#') {
//      digitalWrite(MP,0);
//      Serial.println('#');
//    }
//    else if (in == '='){
//      bluetoothStatus = Serial1.parseInt();
//      if (bluetoothStatus!=5) digitalWrite(MP,0);
//      else digitalWrite(MP,0);
//      Serial.print("W");
//      Serial.println(bluetoothStatus);
//    }
//  }
//  
////  if (Serial2.available()){
////    char in = Serial2.read();
////    if (in == 'd'){
////      float in1 = Serial2.parseFloat();
////      float in2 = Serial2.parseFloat();
////      float in3 = Serial2.parseFloat();
////      float in4 = Serial2.parseFloat();
////      float in5 = Serial2.parseFloat();
////      String R ="R "+String(in1)+' '+String(in2)+' '+String(in3)+' '+String(in4)+' '+String(in5) ;
////      Serial.println(R);
////    }
////    else if (in == 'S') {
////      Serial1.print("Z1r|");
////      S1T = millis();
////    }
////  }
////  
////  if (Serial3.available()){
////    char in = Serial3.read();
////    if (in == 'd'){
////      float in1 = Serial3.parseFloat();
////      float in2 = Serial3.parseFloat();
////      float in3 = Serial3.parseFloat();
////      float in4 = Serial3.parseFloat();
////      float in5 = Serial3.parseFloat();
////      String L ="L "+String(in1)+' '+String(in2)+' '+String(in3)+' '+String(in4)+' '+String(in5) ;
////      Serial.println(L);
////    }
////    else if (in == 'S') {
////      Serial1.print("Z1l|");
////      S1T = millis();
////    }
////  }
//
//  Serial4.listen();
//  delay(20);
//  Serial4.listen();
//  if (Serial4.available()){
//    char in = Serial4.read();
////    Serial.println(in);
//    if (in == 'C'){
//      float disB = Serial4.parseFloat();
//      String C ="C "+String(disB);
//      Serial.println(C);
//      if (disB>100) {
//        Serial1.print("Z1b|");
//        S1T = millis();
//      }
//    }
//    else if (in == 'G'){
//      int tiltA = Serial4.parseInt();
//      String G = "G" + tiltA ;
//      Serial.print(G);
//    }
//    else if (in == 'I'){
//      int RiseA = Serial4.parseInt();
//      String I = "I" + RiseA ;
//      Serial.print(I);
//      Serial2.print(I);
//    }
//    else if (in == 'A'){
//      int Acc = Serial4.parseInt();
//      String A = "A" + Acc ;
//      Serial.print(A);
//    }
//    else if (in == 't'){
//      int temp = Serial4.parseInt();
//      Serial.print("t");
//      Serial.println(temp);
//    }
//  }
//
////  Serial5.listen();
////  delay(20);
////  Serial5.listen();
//  if (Serial3.available()){
//    char in = Serial3.read();
////    Serial.println(in);
//    if (in == 'V'){
//      nowSpeed = Serial3.parseInt();
////      Serial.println(nowSpeed);
//      String send = "V" + String(nowSpeed)+' ';
//      Serial.println(send);
//      Serial1.print('S');
//      Serial1.print(nowSpeed);
//      Serial1.print('|');
//      Serial7.print(send);
//      for (int i = 0 ; i<70 ; i++) Serial2.print(send);
//    }
//  }
//
////  Serial7.listen();
////  delay(20);
////  Serial7.listen();
////  if (Serial7.available()){
////    char in = Serial7.read();
////    if (in == 'X'){
////     int CTRLP = Serial7.parseInt();
////     Serial.print('X');
////     Serial.print(CTRLP); 
////     Serial.print(' ');
////    }
////    else if (in == '^') ;
////    else if (in == 'B') {
////      int batteryP = Serial7.parseInt();
////      String B = "B" + batteryP;
////      Serial.println(B);
////      Serial1.print(B);
////      Serial1.print('|');
////      BP = batteryP;
////      if (batteryP<1000) digitalWrite(41,0);
////    }
////    else if (in =='T'){
////      MT = Serial7.parseInt();
////      Serial.print('T');
////      Serial.println(MT);
////    }
////  }
//
////  Serial8.listen();
////  delay(20);
////  Serial8.listen();
////  if (Serial8.available()){
////    char in = Serial8.read();
////  }
//
////  Serial2.listen();
////  delay(20);
////  Serial2.listen();
//  if (Serial2.available()){
//    char in = Serial2.read();
//    String F = "F";
//    if (in == 'E'){
//      int frontBrakeForce = Serial2.parseInt();
//      Serial.print("E");
//      Serial.print(frontBrakeForce);
//      Serial.println(' ');
//    }
//    else if (in == 'D') {
//      int backBrakeForce = Serial2.parseInt();
//      Serial.print("D");
//      Serial.print(backBrakeForce);
//      Serial.println(' ');
//    }
//    else if (in == 'F'){
//      if (Serial2.available()){
//        char a = Serial2.read();
//        F += a;
//      }
//      Serial.println(F);
//    }
//  }
//
//  if (millis() - S1T < 1000){
//    Serial1.print("Z0|");
//    Serial1.print("Y0|");
//    Serial1.print("X0|");
//  }
//
//
//
//  //======SEND======
//  Serial6.print('B');
//  Serial6.print(BP);
//  Serial6.print('T');
//  Serial6.print(MT);
//  Serial6.print('S');
//  Serial6.print(nowSpeed);
////  Serial6.print('E');
////  Serial6.print(errC.length());
////  Serial6.print(errC);
////  Serial.println("SEOUT");
//}
