void setup() {
  // begin
  Serial.begin(9600);
  Serial10.begin (9600);
  Serial11.begin (9600);
  Serial12.begin(9600);
  Serial13.begin(9600);
  Serial4.begin(9600);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial10.setTimeout(100);
  Serial11.setTimeout(100);
  Serial12.setTimeout(100);
  Serial13.setTimeout(100);
  Serial4.setTimeout(100);
}
