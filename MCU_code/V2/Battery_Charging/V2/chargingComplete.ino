void chargingComplete(){
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
      String out =  "Fully Charged \nCharging Time: " +String (hr)+':'+String (mi)+':'+String(sec);
      Serial.println(out);
      buzzer(55,2);
      buzzer(150,1);
      buzzer(255,1);
      delay(50);
      buzzer(10,2);
      buzzer(255,1);
}
