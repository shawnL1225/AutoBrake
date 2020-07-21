#define motorperPin 20
int nowSpeed = 0 ;
int CTRLP = 0, LCTRLP = 0;

bool motorper = 0;

void setup() {
  pinMode(31,OUTPUT);
  pinMode(30,INPUT_PULLUP);
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(25,OUTPUT);
  digitalWrite(25,0);
  digitalWrite(22,0);
  digitalWrite(24,0);
  digitalWrite(31,0);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  SerialEvent();
  CTRL();
  if (!digitalRead(30)){
    Serial.println("startBrake");
    brake();
  }
}
