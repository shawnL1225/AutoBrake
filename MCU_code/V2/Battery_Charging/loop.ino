void loop() {
  //Take requested number

  while(!Serial.available()&&analogRead(A1)<900){
    if (analogRead(A2)>900||analogRead(A2)<100){
      OLEDwc();
    }
    while(Serial.available()||analogRead(A1)>900){
      if (Serial.available()) in = Serial.parseInt();
      buzzer(50,1);
      buzzer(150,1);
//      else delay(1000);
      
      if (in==1){
        Serial.print("Battery voltage checking procedure launched");
        depani();
        
        //Close Vcc
        Serial.println("VCC CLOSE");
        digitalWrite(2,0);
        delay(300);
        
        //Close GND
        Serial.println("GND CLOSE");
        digitalWrite(3,0);
        delay(300);
        
        Serial.println("VIN OPEN");
        digitalWrite(8,1);
        delay(1000);
        
        // Initilize the PINS for battery voltage
        int Vin = analogRead(A0);
        double BV=Vin*25/1024.0;
  
        //Open GND
        Serial.println("GND Open");
        digitalWrite(3,1);
        delay(300);
        
        //Open Vcc
        Serial.println("VCC Open");
        digitalWrite(2,1);
        delay(300);
  
        //Tell battery voltage
        screen.clearDisplay();
        
        BVC(BV);
        delay(2000);
        
        screen.clearDisplay();
        screen.setCursor(0,15);
        screen.setFont(&FreeSans9pt7b);
        //Tell battery condition
        int per = ((BV-11.4)*100/2.1+0.5);
        if (per<20) {
          Serial.println("<STRONGLY recommand for charging>");
          screen.println("   STRONGLY\n recommand for\n      charging");
        }
        else if (per<50) {
          Serial.println("<Highly recommand for charging>");
          screen.println("      HIGHLY\n   recommand\n   for charging");
        }
        else if (per<75) {
          Serial.println("<Recommand for charging>");
          screen.setCursor(0,30);
          screen.println("   Recommand\n   for charging");
        }
        else if (per>=75) {
          Serial.println("<Battery situation well no need to charge>");
          screen.println("  Situation well \n     no need to \n       charge");
        }
        screen.display();
        Serial.println("");
        delay(3000);

        screen.clearDisplay();
        screen.setCursor(0,15);
        Serial.println("\n<Or REMOVE the power if finish using>\n");
        screen.println("  REMOVE wire \n or RIGHT push  \n    to reselect");
        //reselect the function 
        screen.display();

        while (!Serial.available()&&analogRead(A1)<900);
        showFunc();
        in = 1;

        while(!Serial.available()&&analogRead(A1)<900){
          if (analogRead(A2)>900||analogRead(A2)<100){
            OLEDwc();
          }
        }
      }
      else if (in==2) {
        Serial.print("Charging procedure launched");
        depani();
  
        //VCC Close
        Serial.println("VCC CLOSE");
        digitalWrite(2,0);
        delay(300);
  
        //GND Close
        Serial.println("GND CLOSE");
        digitalWrite(3,0);
        delay(300);
  
        // Initilize the PINS for battery voltage
        int Vin = analogRead(A0);
        double BV=Vin*25/1024.0;
        if (BV < 13.50) {
          screen.clearDisplay();
          BVC(BV);
          delay(2000);
          Serial.println("Start Charging");
          screen.clearDisplay();
          screen.setCursor(5,25);
          screen.setFont(&FreeSans12pt7b);
          screen.println("     Start \n   Charging");
          screen.display();
          Serial.println("Press the button to start charging");
          // if button pressed make VIN's open to close 
          while (digitalRead(12)) ;
          buzzer(255,2);
          Serial.println("VIN CLOSE");
          digitalWrite(8,0);
          delay(100);
          screen.clearDisplay();
          int per = ((BV-11.4)*100/2.1+0.5);
          while (per<100){
            screen.drawBitmap(0, 0, charging_Frame, 128, 64, WHITE);
            screen.display();
            for (int i =0 ; i<75 ; i++){
              screen.drawLine(20+i, 7, 20+i, 71, WHITE);
              screen.display();
              delay(10);
            }
            delay(100);
            screen.clearDisplay();
            if (millis()/(60000*3/*3 minutes*/) > times){
              times++;
              Serial.println("VIN OPEN");
              digitalWrite(8,1);
              delay(3000);
              Vin = analogRead(A0);
              BV=Vin*25/1024.0;
              per = ((BV-11.4)*100/2.1+0.5);
              BVC(BV);
              buzzer(100,1);
              delay(1500);
              screen.clearDisplay();
              if (per<100){
                Serial.println("Keep Charging");
                Serial.println("VIN CLOSE");
                digitalWrite(8,0);
              }
            }
          }
          Serial.println("VIN OPEN");
          digitalWrite(8,1);
          unsigned long msec= millis();
          int sec=0,mi=0,hr=0;
          if (msec%1000>=0){
            sec=msec/1000;
            msec=msec-1000*sec;
            
            if (sec%60>=0){
              mi=sec/60;
              sec=sec-mi*60;
              
              if (mi%60>=0){
                hr=mi/60;
                mi=mi-hr*60;
              }
            }
          }
          Serial.println("GND OPEN");
          digitalWrite(3,1);
          delay(100);
          Serial.println("VCC OPEN");
          digitalWrite(2,1);
          delay(100);
          screen.clearDisplay();
          screen.setCursor(0,15);
          String out =  "  Fully Charged \n Charging Time: \n " +String (hr)+':'+String (mi)+':'+String(sec);
          screen.setFont(&FreeSans9pt7b);
          screen.println(out);
          screen.display();
          buzzer(55,2);
          buzzer(150,1);
          buzzer(255,1);
          delay(50);
          buzzer(10,2);
          buzzer(255,1);
        }
        else if (BV >= 13.50) {
          screen.clearDisplay();
          screen.setCursor(30,0);
          screen.setFont(&FreeSans12pt7b);
          screen.setTextSize(2);
          Serial.print("Battery Voltage:");
          Serial.print(BV);
          Serial.print(" V\t");
          int per = ((BV-11.4)*100/2.1+0.5);
          Serial.print((BV-11.4)*100/2.1);
          if (per<=100||per>=0){
            if (per==100) screen.setCursor(3,48);
            else if(per>=10) screen.setCursor(17,48);
            else if (per<10) screen.setCursor(35,48);
            screen.print(per);
          }
          else {
            screen.setCursor(10,48);
            screen.print("ERR");
          }
          Serial.println(" %");
          screen.println("%");
          screen.display();
          delay(2000);
          Serial.println("Battery Fully Charged");
          screen.clearDisplay();
          screen.setCursor(6,25);
          screen.setFont(&FreeSans12pt7b);
          screen.println("    FULLY \n    Charged");
          screen.display();
          delay(3000);
          
          //Close Vcc
          Serial.println("VCC CLOSE");
          digitalWrite(2,0);
          delay(300);
          
          //Close GND
          Serial.println("GND CLOSE");
          digitalWrite(3,0);
          delay(300);

          screen.clearDisplay();
          screen.setCursor(0,15);
          screen.setFont(&FreeSans9pt7b);
          Serial.println("\n<Or REMOVE the power if finish using>\n");
          screen.println("  REMOVE wire \n or RIGHT push  \n    to reselect");
          //reselect the function 
          screen.display();

          while (!Serial.available()&&analogRead(A1)<900);
          showFunc();
          in = 1;
          
          while(!Serial.available()&&analogRead(A1)<900){
            if (analogRead(A2)>900||analogRead(A2)<100){
              OLEDwc();
            }
          }
        }
      }
      else if (in==0){
        Serial.print("RESET function deploy");
        delay(100);
        Serial.print('.');
        delay(100);
        Serial.print('.');
        delay(100);
        Serial.println('.');
        delay(50);
        resetFunc();
      }
      else if (in== 9){
        screen.clearDisplay();
        screen.drawBitmap(0, 0, setting_logo, 128, 64, WHITE);
        screen.display();
        mil=millis();
        int in9 =Serial.parseInt();
        if (in9 == 2){
          Serial.println("VCC CLOSE");
          digitalWrite(2,0);
          while(!Serial.available());
        }
        else if (in9 == 3){
          Serial.println("GND CLOSE");
          digitalWrite(3,0);
          while(!Serial.available());
        }
        else if (in9 == 8){
          Serial.println("VIN CLOSE");
          digitalWrite(8,0);
          while(!Serial.available());
        }
        else if (in9 == 22){
          Serial.println("VCC OPEN");
          digitalWrite(2,1);
          while(!Serial.available());
        }
        else if (in9 == 33){
          Serial.println("GND OPEN");
          digitalWrite(3,1);
          while(!Serial.available());
        }
        else if (in9 == 88){
          Serial.println("VIN OPEN");
          digitalWrite(8,1);
          while(!Serial.available());
        }
        else if (in9 == 1){
          while(!Serial.available()){
          int Vin = analogRead(A0);
          double BV=Vin*25/1024.0;
          Serial.print("Battery Voltage:");
          Serial.print(BV); 
          Serial.print(" V\t");
          Serial.print("Battery Perecentage:");
          Serial.print((BV-11.4)*100/2.1);
          Serial.println(" %");
          }
        }
        if (millis()-mil<500) {
          Serial.println("You've entered a wrong function");
          Serial.println("Please renter a function");
          Serial.println("\n<Or REMOVE the power if not using>\n");
          while(!Serial.available());
        }
      }
      else {
//        screen.setCursor
        Serial.println("You've entered a wrong function");
        Serial.println("Please renter a function");
        Serial.println("\n<Or REMOVE the power if not using>\n");
        while(!Serial.available());
      }
    }
  }
}
