void setup() {
  //setup
  Serial.begin(9600);
  Serial4.begin(9600);
  dht.begin();
//  mpu6050.begin();
  Serial.println("START");
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
  Serial.println("START");
  pinMode(TP,OUTPUT);
}

void loop() {
//  acc();
  gyro();
  temp();
  ultra();
  send();
}
