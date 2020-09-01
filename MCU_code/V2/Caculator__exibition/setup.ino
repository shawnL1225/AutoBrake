void setup() {
  pinMode(A0,OUTPUT);
  digitalWrite(A0,0);
  // begin
  Serial.begin(9600);
  Serial10.begin(9600);
  Serial11.begin(9600);
  Serial13.begin(9600);
  Serial4.begin(9600);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial10.setTimeout(100);
  Serial11.setTimeout(100);
  Serial13.setTimeout(100);
  Serial4.setTimeout(100);
  
  pinMode(A1,INPUT_PULLUP);
  pinMode(A3,OUTPUT);

  //--MPU6050 Back setup--
  //===============================================================
//  mpu6050.begin();
//  Wire.begin();
//  Wire.beginTransmission(MPU6050BackAddr);
//  Wire.write(0x6B);
//  Wire.write(0);
//  Wire.endTransmission(true);
//
//  //--MPU6050 Front setup--
  Wire.begin();
  Wire.beginTransmission(MPU6050FrontAddr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

//===============================================================
//  gyroBack();
  gyroFront();
  delay(500);
//  gyroBack();
  gyroFront();
  fixFdx = -frontRotateAngle;
//===============================================================
  while (abs(backBrakeForce)>5/*||abs(frontBrakeForce) >5*/){
    SerialEvent();
    Serial10.println("E0");
    Serial11.println("D0");
    Serial11.flush();
    delay(500);
//    digitalWrite(A3,1);
//    delay(40);
//    digitalWrite(A3,0);
//    delay(100);
  }
  Serial10.println("R0");
  Serial11.println("R0");
  Serial11.flush();
  Serial10.println("L0");
  Serial11.println("L0");
  Serial11.flush();
  Serial.println("ALLSET");
  pinMode(A2,INPUT_PULLUP);
  digitalWrite(A0,1);
  digitalWrite(A3,1);
  delay(300);
  digitalWrite(A3,0);
}
