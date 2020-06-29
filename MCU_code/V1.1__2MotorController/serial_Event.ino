// Receive Event [Serial2 -> relay] [Serial1-> cellphone] [Serial3 -> brake]

void serialEvent(){
  int rs;
  //--------------------------------Read--------------------------------
  if (0){
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
  if(Serial1.available()) {
      char in =Serial1.read();
      if(in == '@') {
        int year = Serial1.parseInt();
        int month = Serial1.parseInt();
        int date = Serial1.parseInt();
        int hr = Serial1.parseInt();
        int mi = Serial1.parseInt();
        int sec = Serial1.parseInt();
        int msec = Serial1.parseInt();
        String Ntime = '@'+String(year)+'/'+String(month)+'/'+String(date)+' '+ String(hr)+':'+String(mi)+':'+String(sec)+'.'+String(msec)+" Bike UNLOCK";
        appStart=1;
        lcd.setCursor(0,0);
        lcd.print("0%          ");
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
  
  if(Serial2.available()) {
    char in = Serial2.read();
    if( in== 'V') {
      hv = Serial2.parseInt();
      hv/=100.00;
      if (abs(hv-lhv)<5||lhv!=0||hv-lhv>0){
        String sS ="Speed:"+/*sv+" m/s""\t"*/ String(hv) + " km/hr ";
        lcd.setCursor(0,1);
        lcd.print("Speed:");
        lcd.print(hv);
        lcd.setCursor(10,1);
        lcd.print(" km/hr");
        if (sS!=lsS){
          SDWrite(sS);
          lsS=sS;
          Serial.println(sS);
          // Send Text to Serial1
          hv+=0.5;
          String hvS=String(int(hv));
          Serial1.write('S');
          for (int i=0; i<hvS.length();i++) 
            Serial1.write(hvS[i]);//hv*100
          Serial1.write('|');
          lhv=hv;
        }
      }
      else Serial.println("*********************");
    }
  }
}
