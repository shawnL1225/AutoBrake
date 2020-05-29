// Receive Event [Serial1 -> relay] [Serial2-> cellphone] [Serial3 -> brake]

void serialEvent(){
  int percentage,rs;
  //--------------------------------Read--------------------------------
  if (1){
    if(Serial.available()) {
      char in =Serial.read();
      if(in == '@') {
        unsigned long mtime= millis();
        int amsec=0,asec=0,ami=0,ahr=0;
        if (mtime%1000>0){
          asec=mtime/1000;
          amsec=mtime-1000*asec;
          if (asec%60>0){
            ami=asec/60;
            asec=asec-ami*60;
            if (ami%60>0){
              ahr=ami/60;
              ami=ami-ahr*60;
            }
          }
        }
        int year = Serial.parseInt();
        int month = Serial.parseInt();
        int date = Serial.parseInt();
        int hr = Serial.parseInt();
        int mi = Serial.parseInt();
        int sec = Serial.parseInt();
        int msec = Serial.parseInt();
        int fixmsec = msec - asec;
        String NfileName = String(year)+'-'+String(month)+'-'+String(date)+".txt";
        appStart=1;
        lcd.setCursor(0,0);
        lcd.print("0%            ");
        Serial.println("Bike UNLOCK");
      }
      if (in == '#') {
        lcd.setCursor(0,0);
        lcd.print("LOCK         ");
        appStart=0;
        motor(94, hv, brake);
        SDWrite("Bike LOCK");
        Serial.println("Bike LOCK");
      }
    }
  }
  if (1){
    if(Serial1.available()) {
      if( Serial1.read()== '@') {
        int batteryV = Serial1.parseInt();
        hv = Serial1.parseInt();
        hv/=100.00;
        if (abs(hv-lhv)<400 ){
          String BV="Battery :"+String(batteryV/100.00)+" V";
          if (lBV!=BV) SDWrite(BV);
          lBV=BV;
          percentage=map(batteryV,1050,1350,0,100);
          lcd.setCursor(13,0);
          lcd.print(percentage);
          lcd.print('%');
          String sS ="Speed:"+/*sv+" m/s""\t"*/ String(hv) + " km/hr ";
          lcd.setCursor(0,1);
          lcd.print("Speed:");
          lcd.print(hv);
          lcd.setCursor(10,1);
          lcd.print(" km/hr");
          if (sS!=lsS||BV!=BV){
            SDWrite(sS);
            lsS=sS;
            Serial.print(BV);
            Serial.print("   ");
            Serial.println(sS);
            // Send Text to Serial2
            String hvS=String(int(hv));
            Serial2.write('S');
            for (int i=0; i<hvS.length();i++) 
              Serial2.write(hvS[i]);//hv*100
            Serial2.write('|');
            
            String BpercentageS=String(percentage);
            Serial2.write('B');
            for (int i=0; i<BpercentageS.length();i++) 
              Serial2.write(BpercentageS[i]);//percentage of battery
            Serial2.write('|');
          }
        }
      }
    }
  }
  
  if (1){
    if(Serial2.available()) {
      char in =Serial2.read();
      if(in == '@') {
        int year = Serial2.parseInt();
        int month = Serial2.parseInt();
        int date = Serial2.parseInt();
        int hr = Serial2.parseInt();
        int mi = Serial2.parseInt();
        int sec = Serial2.parseInt();
        int msec = Serial2.parseInt();
        String Ntime = '@'+String(year)+'/'+String(month)+'/'+String(date)+' '+ String(hr)+':'+String(mi)+':'+String(sec)+'.'+String(msec)+" Bike UNLOCK";
        appStart=1;
        lcd.setCursor(0,0);
        lcd.print("0%            ");
        SDWrite(Ntime);
        Serial.println("Bike UNLOCK");
      }
      if (in == '#') {
        lcd.setCursor(0,0);
        lcd.print("LOCK      ");
        appStart=0;
        motor(94, hv, brake);
        SDWrite("Bike LOCK");
        Serial.println("Bike LOCK");
      }
    }
  }
  
  if (0){
    if(Serial3.available()) {
      if('@' != Serial3.read()) { 
          int n = Serial3.parseInt();
              bool isConnect = bool(n);
              digitalWrite(VGALED,isConnect);
              Serial.print(n);
          int a = Serial3.parseInt();
              brake = bool(a);
              Serial.println(a);
      }
    }
  }
  
  // -------------------------------Write--------------------------
  // Receive Event [Serial1 -> relay] [Serial2-> cellphone] [Serial3 -> brake]
  //-------------------1relay---------------------
    //Send Speed to 1relay
    if (0){
      Serial1.write('@');
      Serial1.print("");
    }
    
  //------------------2cellphone---------------------
    //Send Speed to Cellphone
    if (0){
      String RASPXpowerpS = String (RASPXpowerp);
      for(int i=0; i<RASPXpowerpS.length();i++)
        Serial2.write(RASPXpowerpS[i]);
      Serial2.write('|');
    }
    
  //----------------3brake------------------------
    if (0){
      Serial3.write('@');
      if (digitalRead(3)) Serial3.write('1');
      else Serial3.write('0');
      Serial3.write(' ');
    }
}
