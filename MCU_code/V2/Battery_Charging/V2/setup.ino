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

  // Initilize the PINS for button
  pinMode(10,OUTPUT);
  digitalWrite(10,0);
  pinMode(12,INPUT_PULLUP);
  buzzer(Do,1);
  buzzer(Re,1);
  buzzer(Me,1);
  buzzer(Fa,1);
  buzzer(So,1);
  buzzer(Fa,1);
  buzzer(Me,1);
  buzzer(Re,1);
  buzzer(Do,1);
  Serial.println("Charging procedure launched");

  //VCC Close
  Serial.println("VCC CLOSE");
  digitalWrite(2,0);
  delay(100);

  //GND Close
  Serial.println("GND CLOSE");
  digitalWrite(3,0);
  delay(100);

  int Vin = analogRead(A0);
    double BV=Vin*25/1024.0;
    if (BV < 13.50) {
      cp = 1;
      BVC(BV);
      delay(400);
      Serial.println("Press the button to start charging");
      while (digitalRead(12)) ;
      Serial.println("Start Charging");
      // if button pressed make VIN's open to close 
      buzzer(Do,1);
      buzzer(Me,1);
      buzzer(Fa,1);
      Serial.println("VIN CLOSE");
      digitalWrite(8,0);
    }
    else if (BV >= 13.50){
      cp = 0;
    }
}
