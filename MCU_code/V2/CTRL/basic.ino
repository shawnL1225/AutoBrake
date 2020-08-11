void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.print("");

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(7,OUTPUT);
  pinMode(8,INPUT_PULLUP);
  
  pinMode(A1,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  
  Serial.println("START");
}

void loop() {
  CTRL();
  battery();
  serialEvent();
  if (!digitalRead(2)&&!digitalRead(3)&&SB) digitalWrite(7,1);
  else digitalWrite(7,0);
//  ifOverSpeed();
}
