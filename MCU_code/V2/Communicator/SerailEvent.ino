// Receive Event [Serial1 -> motor_with_battery_brakeD_CTRL] [Serial2-> cellphone] [Serial3 -> Speed Sensor Error]

int RASPXpowerp;

void serialEvent(){
  //--------------------------------Read--------------------------------
  if (1){ //Serial
    if(Serial.available()) {
    }
  }
  
  if (1){ //Serial1
    if(Serial1.available()) {
      char in =Serial1.read();
        if (in=='P'){
          int ASPXpower = Serial1.parseInt();
          Serial.print(ASPXpower);
          lcd.setCursor(0,0);
          if ((ASPXpower-94)<0) RASPXpowerp=0;
          else RASPXpowerp=(ASPXpower-94)*100/51;
          lcd.print(RASPXpowerp);
          lcd.print("%       ");
          String RASPXpowerpS = String (RASPXpowerp);
          Serial2.write('M');
          for(int i=0; i<RASPXpowerpS.length();i++)
             Serial2.write(RASPXpowerpS[i]);
          Serial2.write('|');
        }
        if (in=='V'){
          int batteryV = Serial1.parseInt();
          Serial.print("Battery Voltage : ");
          Serial.print(batteryV);
          Serial.println(" V");
        }
        if (in=='^'){
          Serial.println("Button Pressed");
        }
        if (in=='#'){
          Serial.println("Brake applied");
        }
        if (in=='E'){
          Serial.println("CTRL　Error　Occur");
        }
        if (in=='S'){
          Serial.println("CTRL Error Solved");
        }
      }
    }
  
  if (1){ //Serial2
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
        lcd.print("0%          ");
        SDWrite(Ntime);
        Serial.println("Bike UNLOCK");
        Serial1.write('@');
      }
      if (in == '#') {
        lcd.setCursor(0,0);
        lcd.print("LOCK      ");
        appStart=0;
        SDWrite("Bike LOCK");
        Serial.println("Bike LOCK");
        Serial1.write('%');
      }
    }
  }
  
  if (1){ //Serial3
    if(Serial3.available()) {
      char in =Serial3.read();
      if(in == 'V') {
        int Speed = Serial3.parseInt();
        Serial.print("Speed : ");
        Serial.print(Speed/100.00);
        Serial.println("km/hr");
      }
      if(in == 'E') {
        Serial.println("Speed sensor error");
      }
    }
  }
  
}
