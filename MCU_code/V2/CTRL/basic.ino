void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.print("");
  Serial.println("\nbegin");

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(7,OUTPUT);
  pinMode(8,INPUT_PULLUP);
  
  pinMode(A1,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  
  Serial.println("\nbegin");
}

void loop() {
  CTRL();
  battery();
  serialEvent();
  motorper = (!digitalRead(2)&&!digitalRead(3));
  if (motorper) digitalWrite(7,1);
  else digitalWrite(7,0);
//  speed();
}
