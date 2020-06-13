void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.print(' ');
  Serial.println("\nbegin");
  pinMode(8,INPUT_PULLUP);
  Serial.println("\nbegin");
}

void loop() {
  CTRL();
  battery();
  serialEvent();
//  brakeDetect();
}
