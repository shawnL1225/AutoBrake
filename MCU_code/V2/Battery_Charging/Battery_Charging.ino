int times = 0;
unsigned long mil=0;

void setup() {
  // Ask PINS to be low 
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(2,1);
  digitalWrite(3,1);
  digitalWrite(8,1);
  delay(1000);
  
  // Serial begin 
  Serial.begin(9600);
//  Serial.println("Ready for charging");
  Serial.println("");

  // Initilize the PINS for button
  pinMode(10,OUTPUT);
  digitalWrite(10,0); 
  pinMode(12,INPUT_PULLUP);

  //Request for method
  Serial.println("Hello and thank you for use <AutoBrake Battery Charging Ststem>");
  delay(100);
  Serial.println("Please Select the function below");
  Serial.println("1. Check the Battery Voltage");
  Serial.println("2. Let the battery charge\n");

  //Take requested number
  while(!Serial.available());
  while(Serial.available()){
    int in = Serial.parseInt();
    if (in==1){
      Serial.print("Battery voltage checking procedure launched");
      delay(100);
      Serial.print('.');
      delay(100);
      Serial.print('.');
      delay(100);
      Serial.println('.');
      
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
      Serial.print("Battery Voltage");
      Serial.print(BV);
      Serial.print(" V\t");
      Serial.print("Battery Perecentage");
      Serial.print((BV-11.4)*100/2.1);
      Serial.println(" %");
      
      //Tell battery condition
      if (BV<11) Serial.println("<STRONGLY recommand for charging>");
      else if (BV<12) Serial.println("<Highly recommand for charging>");
      else if (BV<13) Serial.println("<Recommand for charging>");
      else if (BV>13.50) Serial.println("<Battery situation well no need to charge>");
      Serial.println("");
      delay(1000);
      Serial.println("Please Select the function below");
      Serial.println("1. Check the Battery Voltage");
      Serial.println("2. Let the battery charge");
      delay(1000);
      Serial.println("\n<Or REMOVE the power if finish using>\n");
      while (!Serial.available());
    }
    else if (in==2) {
      Serial.print("Charging procedure launched");
      delay(100);
      Serial.print('.');
      delay(100);
      Serial.print('.');
      delay(100);
      Serial.println('.');

      //VCC Close
      Serial.println("VCC CLOSE");
      digitalWrite(2,0);
      delay(300);

      //GND Close
      Serial.println("GND CLOSE");
      digitalWrite(3,0);
      delay(300);

      Serial.println("Press the button to start charging");
      // if button pressed make VIN's open to close 
      while (digitalRead(12)) ;

      // Initilize the PINS for battery voltage
      int Vin = analogRead(A0);
      double BV=Vin*25/1024.0;
      if (BV < 13.50) {
        Serial.print("Battery Voltage:");
        Serial.print(BV);
        Serial.print(" V\t");
        Serial.print("Battery Perecentage:");
        Serial.print((BV-11)*100/2.1);
        Serial.println(" %");
        Serial.println("Start Charging");
        Serial.println("VIN CLOSE");
        digitalWrite(8,0);
        delay(100);
      }
      else if (BV >= 13.50) {
        Serial.println("VIN OPEN");
        digitalWrite(8,1);
        delay(100);
        Serial.println("GND OPEN");
        digitalWrite(3,1);
        delay(100);
        Serial.println("VCC OPEN");
        digitalWrite(2,1);
        Serial.print("Battery Voltage:");
        Serial.print(BV);
        Serial.print(" V\t");
        Serial.print("Battery Perecentage:");
        Serial.print((BV-11)*100/2.1);
        Serial.println(" %");
        Serial.println("Battery Fully Charged");
        while(1);
      }
    }
    else if (in==9){
      mil=millis();
      int in9 =Serial.parseInt();
      if (in9 ==2){
        Serial.println("VCC CLOSE");
        digitalWrite(2,0);
        while(!Serial.available());
      }
      else if (in9 ==3){
        Serial.println("GND CLOSE");
        digitalWrite(3,0);
        while(!Serial.available());
      }
      else if (in9 ==8){
        Serial.println("VIN CLOSE");
        digitalWrite(8,0);
        while(!Serial.available());
      }
      else if (in9 ==22){
        Serial.println("VCC OPEN");
        digitalWrite(2,1);
        while(!Serial.available());
      }
      else if (in9 ==33){
        Serial.println("GND OPEN");
        digitalWrite(3,1);
        while(!Serial.available());
      }
      else if (in9 ==88){
        Serial.println("VIN OPEN");
        digitalWrite(8,1);
        while(!Serial.available());
      }
      else if (in9 ==1){
        
        while(!Serial.available()){
        int Vin = analogRead(A0);
        double BV=Vin*25/1024.0;
        Serial.print("Battery Voltage1:");
        Serial.print(BV); 
        Serial.print(" V\t");
        Serial.print("Battery Perecentage:");
        Serial.print((BV-11.4)*100/2.1);
        Serial.println(" %");
        
        Vin = analogRead(A1);
        BV=map(Vin,0,1023,0,15.00);
        Serial.print("Battery Voltage2:");
        Serial.print(BV); 
        Serial.print(" V\t");
        Serial.print("Battery Perecentage:");
        Serial.print((BV-11.4)*100/2.1);
        Serial.println(" %");

        Vin = analogRead(A2);
        BV=Vin*25/1024.0;
        Serial.print("Battery Voltage3:");
        Serial.print(BV); 
        Serial.print(" V\t");
        Serial.print("Battery Perecentage:");
        Serial.print((BV-11.4)*100/2.1);
        Serial.println(" %\n");

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
      Serial.println("You've entered a wrong function");
      Serial.println("Please renter a function");
      Serial.println("\n<Or REMOVE the power if not using>\n");
      while(!Serial.available());
    }
  }
}


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
  if (millis()/(60000*3) > times){
    times++;
    Serial.println("VIN OPEN");
    digitalWrite(8,1);
    delay(1500);
    int Vin = analogRead(A0);
    double BV=Vin*25/1024.0;
    if (BV >13.50){
      Serial.print("Battery Voltage:");
      Serial.print(BV); 
      Serial.print(" V\t");
      Serial.print("Battery Perecentage:");
      Serial.print((BV-11.4)*100/2.1);
      Serial.println(" %");
      Serial.println("Charging Complete");
      Serial.println("GND OPEN");
      digitalWrite(3,1);
      Serial.println("VCC OPEN");
      digitalWrite(2,1);
      delay(100);
      while(1);
    }
    else {
      Serial.print("Battery Voltage:");
      Serial.print(BV); 
      Serial.print(" V\t");
      Serial.print("Battery Perecentage:");
      Serial.print((BV-11.4)*100/2.1);
      Serial.println(" %");
      Serial.println("Keep Charging");
      Serial.println("VIN CLOSE");
      digitalWrite(8,0);
    } 
  }
}
