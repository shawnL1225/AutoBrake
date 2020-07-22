void setup() {
  // begin
  Serial.begin(9600);
  Serial1.begin (9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial4.begin(9600);
  Serial5.begin(9600);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial1.setTimeout(100);
  Serial2.setTimeout(100);
  Serial3.setTimeout(100);
  Serial4.setTimeout(100);
  Serial5.setTimeout(100);
}
