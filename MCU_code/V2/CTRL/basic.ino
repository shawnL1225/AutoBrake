void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.print("");

  pinMode(2,OUTPUT);
  pinMode(12,INPUT_PULLUP);
  
  pinMode(A3,INPUT);
  pinMode(A7,INPUT);
  
  Serial.println("START");
  Serial.flush();
}

void loop() {
  CTRL();
  battery();
  serialEvent();
  if (!digitalRead(12)&&SB&&BOK) digitalWrite(2,1);
  else digitalWrite(2,0);
//  ifOverSpeed();
}
