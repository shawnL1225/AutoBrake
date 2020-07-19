#define motorperPin 20
int nowSpeed = 0 ;
int CTRLP = 0, LCTRLP = 0;

bool motorper = 0;

void setup() {
  pinMode(31,OUTPUT);
  digitalWrite(31,1);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(30,INPUT);
  digitalWrite(31,0);
}

void loop() {
  SerialEvent();
  CTRL();
  if (digitalRead(30)){
    brake();
  }
}
