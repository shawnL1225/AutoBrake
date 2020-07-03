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
  Serial.println("");

  //Monitor begin
  screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
  screen.clearDisplay();  // Clear the buffer
  screen.setTextColor(WHITE);  // Set color of the text
  screen.setFont();
  screen.setFont(&FreeSans9pt7b);

  screen.drawBitmap(0, 0, autobrake_logo, 128, 64, WHITE);
  delay(1000);
  screen.clearDisplay();
  screen.drawBitmap(0, 0, charging_logo, 128, 64, WHITE);
  delay(1000);
  screen.clearDisplay();

  // Initilize the PINS for button
  pinMode(10,OUTPUT);
  digitalWrite(10,0); 
  pinMode(12,INPUT_PULLUP);

  //Say Hello
  Serial.println("Hello and thank you for using <AutoBrake Battery Charging Ststem>");
  screen.setFont();
  screen.setCursor(30, 0); // (x,y)
  screen.println("Hello and thank you for using <AutoBrake Battery Charging Ststem>");
  delay(500);
  screen.clearDisplay();
  
  //Request for method
  screen.setCursor(30, 0); // (x,y)
  Serial.println("Please Select the function below");
  screen.println("Please Select the function below");
  Serial.println("1. Check the Battery Voltage");
  screen.println("1. Check the Battery Voltage");
  Serial.println("2. Let the battery charge\n");
  screen.println("2. Let the battery charge\n");

  //Take requested number
  while(!Serial.available());
  while(Serial.available()){ 
    int in = Serial.parseInt();
    if (in==1){
      screen.clearDisplay();
      screen.setCursor(30, 0); // (x,y)
      Serial.print("Battery voltage checking procedure launched");
      screen.print("Battery voltage checking procedure launched");
      delay(100);
      Serial.print('.');
      screen.print('.');
      delay(100);
      Serial.print('.');
      screen.print('.');
      delay(100);
      Serial.println('.');
      screen.print('.');
      
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
      screen.setCursor(60,0);
      Serial.print("Battery Voltage");
      screen.print("Battery Voltage");
      Serial.print(BV);
      screen.print(BV);
      Serial.print(" V\t");
      screen.print(" V\t");
      Serial.print("Battery Perecentage");
      screen.print("Battery Perecentage");
      Serial.print((BV-11.4)*100/2.1);
      screen.print((BV-11.4)*100/2.1);
      Serial.println(" %");
      screen.println(" %");
      
      //Tell battery condition
      if (BV<11) {
        Serial.println("<STRONGLY recommand for charging>");
        screen.println("<STRONGLY recommand for charging>");
      }
      else if (BV<12) {
        Serial.println("<Highly recommand for charging>");
        screen.println("<Highly recommand for charging>");
      }
      else if (BV<13) {
        Serial.println("<Recommand for charging>");
        screen.println("<Recommand for charging>");
      }
      else if (BV>13.50) {
        Serial.println("<Battery situation well no need to charge>");
        screen.println("<Battery situation well no need to charge>");
      }
      Serial.println("");
      screen.println("");
      delay(5000);

      //reselect the function 
      screen.clearDisplay();
      Serial.println("Please Select the function below");
      screen.println("Please Select the function below");
      Serial.println("1. Check the Battery Voltage");
      screen.println("1. Check the Battery Voltage");
      Serial.println("2. Let the battery charge");
      screen.println("2. Let the battery charge");
      delay(1000);
      Serial.println("\n<Or REMOVE the power if finish using>\n");
      screen.println("\n<Or REMOVE the power if finish using>\n");
      while (!Serial.available());
    }
    else if (in==2) {
      screen.clearDisplay();
      screen.setCursor(30, 0); // (x,y)
      Serial.print("Charging procedure launched");
      screen.print("Charging procedure launched");
      delay(100);
      Serial.print('.');
      screen.print('.');
      delay(100);
      Serial.print('.');
      screen.print('.');
      delay(100);
      Serial.println('.');
      screen.println('.');

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
        Serial.println("Start Charging");
        screen.println("Start Charging");
        Serial.println("VIN CLOSE");
        digitalWrite(8,0);
        delay(100);
      }
      else if (BV >= 13.50) {
        screen.clearDisplay();
        screen.setCursor(30,0);
        Serial.println("VIN OPEN");
        digitalWrite(8,1);
        delay(100);
        Serial.println("GND OPEN");
        digitalWrite(3,1);
        delay(100);
        Serial.println("VCC OPEN");
        digitalWrite(2,1);
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
        Serial.println("Battery Fully Charged");
        screen.println("Battery Fully Charged");
        while(1);
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
        Serial.print("Battery Voltage1:");
        Serial.print(BV); 
        Serial.print(" V\t");
        Serial.print("Battery Perecentage:");
        Serial.print((BV-11.4)*100/2.1);
        Serial.println(" %");
        }
      }
      if (millis()-mil<500) {
        screen.clearDisplay();
        screen.setCursor(30,0);    //(X,Y)
        Serial.println("You've entered a wrong function");
        screen.println("You've entered a wrong function");
        Serial.println("Please renter a function");
        screen.println("Please renter a function");
        Serial.println("\n<Or REMOVE the power if not using>\n");
        screen.println("\n<Or REMOVE the power if not using>\n");
        while(!Serial.available());
      }
    }
    else {
      screen.clearDisplay();
      screen.setCursor(30,0);    //(X,Y)
      Serial.println("You've entered a wrong function");
      screen.println("You've entered a wrong function");
      Serial.println("Please renter a function");
      screen.println("Please renter a function");
      Serial.println("\n<Or REMOVE the power if not using>\n");
      screen.println("\n<Or REMOVE the power if not using>\n");
      while(!Serial.available());
    }
  }
}
