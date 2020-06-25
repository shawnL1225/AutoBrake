int times = 0;

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
  Serial.println("Ready for charging");

  // Initilize the PINS for button
  pinMode(10,OUTPUT);
  digitalWrite(10,0); 
  pinMode(12,INPUT_PULLUP);

  // if button pressed make VCCs' open to close 
  while (digitalRead(12));
  Serial.println("VCC CLOSE");
  digitalWrite(2,0);
  delay(300);

  // if button pressed make GNDs' open to close 
  while (digitalRead(12)) ;
  Serial.println("GND CLOSE");
  digitalWrite(3,0);
  delay(300);

  // if button pressed make VIN's open to close 
  while (digitalRead(12)) ;
  Serial.println("VIN  CLOSE");
  digitalWrite(8,0);
  delay(100);
  
  // Initilize the PINS for battery voltage
  int Vin = analogRead(A0);
  double BV=Vin*5/1024.0/(7500/37500);
  if (BV < 13.10) {
    digitalWrite(8,0);
    Serial.println("Start Charging");
  }
  else if (BV > 13.00) {
    Serial.println("Battery Fully Charged");
    digitalWrite(8,1);
    delay(100);
    digitalWrite(3,1);
    delay(100);
    digitalWrite(2,1);
    Serial.print("Now Battery Voltage");
    Serial.print(BV); 
    Serial.println(" V");
    Serial.print("Now Battery Perecentage");
    Serial.print((BV-11)*100/2.1);
    Serial.println(" %");
//    while(1);
  }
}

void loop() {
    int Vin = analogRead(A0);
    double BV=Vin*5/1024.0/(7500/37500);
    Serial.print("Now Battery Voltage");
    Serial.print(BV); 
    Serial.println(" V");
    Serial.print("Now Battery Perecentage");
    Serial.print((BV-11)*100/2.1);
    Serial.println(" %");
//    while(1);
  //Check Battery Voltage once per min
  unsigned long mil = millis();
  if (mil/60000 > times){
    times++;
    digitalWrite(8,1);
    delay(50);
    int Vin = analogRead(A0);
    double BV=Vin*5/1024.0/(7500/37500);
    if (BV >1310){
      Serial.println("Charging Complete");
      digitalWrite(2,1);
      delay(100);
      digitalWrite(3,1);
      Serial.print("Now Battery Voltage");
      Serial.print(BV); 
      Serial.println(" V");
      Serial.print("Now Battery Perecentage");
      Serial.print((BV-11)*100/2.1);
      Serial.println(" %");
      while(1);
    }
    else {
      digitalWrite(8,1);
      Serial.println("Keep Charging");
      Serial.print("Now Battery Voltage");
      Serial.print(BV); 
      Serial.println(" V");
      Serial.print("Now Battery Perecentage");
      Serial.print((BV-11)*100/2.1);
      Serial.println(" %");
    } 
  }
}
