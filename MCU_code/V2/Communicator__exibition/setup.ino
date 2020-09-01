void setup() {
  // begin
  Serial.begin(19200);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial4.begin(9600);
//  Serial5.begin(9600);
//  Serial9.begin(9600);
//  Serial7.begin(9600);
//  Serial8.begin(9600);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial1.setTimeout(100);
  Serial2.setTimeout(100);
  Serial3.setTimeout(100);
  Serial4.setTimeout(100);
//  Serial5.setTimeout(100);
//  Serial9.setTimeout(100);
//  Serial7.setTimeout(100);
//  Serial8.setTimeout(100);

  pinMode(MP,OUTPUT);
  digitalWrite(MP,1);
  
  
  //------------------===== SD Check ====-------------
    int a = 0;
    if (!SD.begin(12/*CS port*/)) {
      Serial.println("HSD Error");
      a++;
      if (a<=5) return;
    }
    else {
      errC = "E";
    }
    
  //--------------------------board check----------------------------
    boardCheck();
    // RTC Setup
    if (!rtc.begin() || !rtc.isrunning()) {
      Serial.println("HRTC Error");
      RTCS = 0;
    }
    
// ----------------------Name a file name------------------
    if (RTCS){
      dt = rtc.now();
      int YYYY = dt.year();
      int MM = dt.month();
      int DD = dt.day();
      fileName = (String(YYYY)+'_'+String(MM)+'_'+String(DD)+".TXT");
      Serial.println(fileName);
      file.close();
    }
    else {
      file = SD.open("fileNo.txt");
      int fileNo = file.parseInt();
      fileName=String(fileNo)+".TXT";
      fileNo++;
      file.close();
      SD.remove("fileNo.txt");
      file = SD.open("fileNo.txt",FILE_WRITE);
      file.println(fileNo);
      file.close();
    }
    SDWrite("setup accomplish");
    SDWrite(errC);
    batteryP= (random(90,92));
    
//  -------------------------MPU6050----------------------------
//    Wire.begin();
//    Wire.beginTransmission(MPU6050_addr);
//    Wire.write(0x6B);
//    Wire.write(0);
//    Wire.endTransmission(true);
//    gyro();
//    fixdx=-dx;
//    fixdy=-dy;
//    fixdz=-dz;
}
