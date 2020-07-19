void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);


}

void loop() {
  if(Serial1.available()>0)
  {
    float a = Serial1.parseFloat();
    Serial.println(a);
  }

}
