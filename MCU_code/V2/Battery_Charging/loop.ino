void loop() {
  
  //Show battery voltage when charging
  int Vin = analogRead(A0);
  double BV=Vin*25/1024.0;
  Serial.print("Battery Voltage:");
  Serial.print(BV); 
  Serial.print(" V\t");
  Serial.print("Battery Perecentage:");
  Serial.print((BV-11.4)*100/2.1);
  Serial.println(" %");
  delay(1000);

  //Check Battery Voltage once per min
  if (millis()/(60000*3/*3 minutes*/) > times){
    times++;
    Serial.println("VIN OPEN");
    digitalWrite(8,1);
    delay(1500);
    int Vin = analogRead(A0);
    double BV=Vin*25/1024.0;
    if (BV >13.50){
      screen.clearDisplay();
      screen.setCursor(30,0);
      Serial.print("Battery Voltage:");
      screen.print("Battery Voltage:");
      Serial.print(BV);
      screen.print(BV);
      Serial.print(" V\t");
      screen.print(" V\n");
      Serial.print("Battery Perecentage:");
      screen.print("Battery Perecentage:");
      Serial.print((BV-11)*100/2.1);
      screen.print((BV-11)*100/2.1);
      Serial.println(" %");
      screen.println(" %");
      Serial.println("Charging Complete");
      screen.println("Charging Complete");
      Serial.println("GND OPEN");
      digitalWrite(3,1);
      Serial.println("VCC OPEN");
      digitalWrite(2,1);
      delay(100);
      while(1);
    }
    
    else {
      screen.clearDisplay();
      screen.setCursor(30,0);
      Serial.print("Battery Voltage:");
      screen.print("Battery Voltage:");
      Serial.print(BV);
      screen.print(BV);
      Serial.print(" V\t");
      screen.print(" V\n");
      Serial.print("Battery Perecentage:");
      screen.print("Battery Perecentage:");
      Serial.print((BV-11)*100/2.1);
      screen.print((BV-11)*100/2.1);
      Serial.println(" %");
      screen.println(" %");
      Serial.println("Keep Charging");
      screen.println("Keep Charging");
      Serial.println("VIN CLOSE");
      digitalWrite(8,0);
    }
    
    if (Serial.available()){
      if (Serial.parseInt()==0){
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
    }
  }
}
