void setup() {
  //setup
  Serial.begin(9600);
  dht.begin();
  mpu6050.begin();
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  //Error dectect
  temp();
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT Sensor Error");
  }
  Serial.println("OK");
  acc();
  gyro();
  fixax=-ax;
  fixay=-ay;
  fixaz=-az;
  fixdx=-dx;
  fixdy=-dy;
  fixdz=-dz;
}

void loop() {
  acc();
  gyro();
  temp();
  send();
}
