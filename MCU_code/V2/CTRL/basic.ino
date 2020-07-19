void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.print("");
  Serial.println("\nbegin");
  pinMode(8,INPUT_PULLUP);
  pinMode(A1,INPUT);
  Serial.println("\nbegin");
}

void loop() {
  CTRL();
  battery();
  serialEvent();
  motorper = (digitalRead(2)&&digitalRead(3));
//  speed();
}
