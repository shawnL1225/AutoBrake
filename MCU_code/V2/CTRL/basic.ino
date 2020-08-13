void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.print("");

  pinMode(12,INPUT_PULLUP);
  pinMode(2,OUTPUT);
  
  pinMode(A7,INPUT);
  pinMode(A3,INPUT);
  
  Serial.println("START");
}

void loop() {
  CTRL();
  battery();
  serialEvent();
  if (!digitalRead(12)&&SB&&BOK) digitalWrite(2,1);
  else digitalWrite(2,0);
//  ifOverSpeed();
}
