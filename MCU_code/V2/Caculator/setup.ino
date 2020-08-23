void setup() {
  pinMode(A0,OUTPUT);
  digitalWrite(A0,0);
  // begin
  Serial.begin(9600);
  Serial10.begin(9600);
  Serial11.begin(9600);
//  Serial12.begin(9600);
  Serial13.begin(9600);
  Serial4.begin(9600);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial10.setTimeout(100);
  Serial11.setTimeout(100);
//  Serial12.setTimeout(100);
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
//  Wire.begin();
//  Wire.beginTransmission(MPU6050FrontAddr);
//  Wire.write(0x6B);
//  Wire.write(0);
//  Wire.endTransmission(true);
//===============================================================

  int a = 0;
  if (!SD.begin(10/*CS port*/)) {
    Serial.println("SD Error");
    a++;
//    if (a<=5) return;
    pinMode(13,OUTPUT);
    digitalWrite(13,1);
    digitalWrite(A3,1);
    delay(1000);
    digitalWrite(A3,0);
    digitalWrite(A0,1);
    while(1);
  }
  else {
    Serial.println("SD OK");
    SerialEvent();
    delay(100);
    while (abs(backBrakeForce)>5||abs(frontBrakeForce)>5){
      SerialEvent();
      Serial10.println("E0");
      Serial11.println("D0");
      Serial11.flush();
      digitalWrite(A3,1);
      delay(40);
      digitalWrite(A3,0);
      delay(100);
    }

//===============================================================
//  gyroBack();
//  gyroFront();
//  delay(500);
//  gyroBack();
//  gyroFront();
//===============================================================

//  fixFdx = -frontRotateAngle;

    file = SD.open("frontF.txt");
    RFF = file.parseInt();
    file.close();
    file = SD.open("backF.txt");
    RBF = file.parseInt();
    file.close();
    file = SD.open("Speed.txt");
    expSetSpeed = file.parseInt();
    file.close();
    file = SD.open("NO.txt");
    NO = file.parseInt();
    NO++;
    file.close();
    SD.remove("NO.txt");
    file = SD.open("NO.txt",FILE_WRITE);
    file.println(NO);
    file.close();
    fileName = String(NO)+".txt";
    file = SD.open(fileName,FILE_WRITE);
    file.print(millis());
    file.print("\tSTART RECORD\n");
    file.print("FileNo."+String(NO)+'\t'+"Front Force: "+String(RFF)+'\t'+"Back Force: "+String(RBF)+'\t'+"setSpeed: "+String(expSetSpeed)+'\n');
    file.close();
    Serial.print(String(RBF)+'\t'+String(RFF)+'\t'+String(expSetSpeed)+'\t'+String(NO)+'\n');

    Serial10.println("R0");
    Serial11.println("R0");
    Serial11.flush();
    Serial10.println("L0");
    Serial11.println("L0");
    Serial11.flush();
    Serial.println("ALLSET");
    digitalWrite(A0,1);
    digitalWrite(A3,1);
    delay(200);
    digitalWrite(A3,0);
  }
}
