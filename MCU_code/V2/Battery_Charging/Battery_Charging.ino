int times = 0;

void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(A0,INPUT);
  digitalWrite(3,1);
  delay(200);
  digitalWrite(2,1);
  delay(200);
  digitalWrite(8,0);
  delay(100);
  int V = analogRead(A0);
  V*=3;
  int BV = map (V , 0,3069,0,1500);
  if (BV < 1350) {
    digitalWrite(8,1);
    Serial.println("Start Charging");
  }
  else if (BV > 1350) {
    Serial.println("Battery Fully Charged");
    digitalWrite(2,0);
    delay(100);
    digitalWrite(3,0);
    Serial.print(BV/100.00-.4); 
    Serial.println(" V");
  }
}

void loop() {
  //Tell the Battery Voltage
  int V = analogRead(A0);
  V*=3;
  double BV = map (V , 0,3069,0,1500);
  Serial.print(V/3);
  Serial.print("\t");
  Serial.print(BV/100.00-.4);
  Serial.println(" V");
  delay(500);

  //Check Battery Voltage once per min
  unsigned long mil = millis();
  if (mil/60000 > times){
    times++;
    if (BV>1350){
      digitalWrite(8,0);
      delay(50);
      V = analogRead(A0);
      V*=3;
      BV = map (V , 0,3069,0,1500);
      if (BV >1350){
        Serial.println("Charging Complete");
        digitalWrite(2,0);
        delay(100);
        digitalWrite(3,0);
        while(1);
      }
      else {
        digitalWrite(8,1);
        Serial.println("Keep Charging");
      }
    }
    else if (BV<=1350){
      digitalWrite(8,1);
      Serial.println("Keep Charging");
    }
  }
}
