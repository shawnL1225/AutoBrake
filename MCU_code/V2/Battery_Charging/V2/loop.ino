void loop() {
  if (cp){
    int Vin = analogRead(A0);
    double BV=Vin*25/1024.0;
    if (BV < 13.50) {
      if (millis()/(60000*3/*3 minutes*/) > times){
        times++;
        Serial.println("VIN OPEN");
        digitalWrite(8,1);
        delay(3000);
        Vin = analogRead(A0);
        BV=Vin*25/1024.0;
        BVC(BV);
        buzzer(3951,1);
        if (BV<13.4){
          Serial.println("Keep Charging");
          Serial.println("VIN CLOSE");
          digitalWrite(8,0);
        }
        else chargingComplete();
      }
    }
    else chargingComplete();
  }

  if (Serial.available()){
    char in = Serial.read();
    if (in== '$'){
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
    }
  }
}
