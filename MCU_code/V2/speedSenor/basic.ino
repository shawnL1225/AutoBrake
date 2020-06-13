void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
}

void loop() {
  speedSensor();
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
}
