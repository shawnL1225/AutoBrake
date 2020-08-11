void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(5,1);
  digitalWrite(6,1);
  Serial.println("READY");
  Serial.println("BEGIN");
  delay(1000);
  Serial4.print("O ");
}

void loop() {
  speedSensor();
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
}
