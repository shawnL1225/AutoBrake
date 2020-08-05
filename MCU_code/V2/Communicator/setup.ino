void setup() {
  // begin
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial4.begin(9600);
  Serial5.begin(9600);
  Serial9.begin(9600);
  Serial7.begin(9600);
  Serial8.begin(9600);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial1.setTimeout(100);
  Serial2.setTimeout(100);
  Serial3.setTimeout(100);
  Serial4.setTimeout(100);
  Serial5.setTimeout(100);
  Serial9.setTimeout(100);
  Serial7.setTimeout(100);
  Serial8.setTimeout(100);

  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);
  pinMode(S7,INPUT);
  pinMode(S8,INPUT);
  pinMode(S9,INPUT);
  pinMode(S10,INPUT);
  pinMode(S11,INPUT);
  pinMode(S12,INPUT);
  pinMode(S13,INPUT);
  pinMode(MP,OUTPUT);
  digitalWrite(MP,0);
  
  
  //------------------===== SD Check ====-------------
    int a = 0;
    if (!SD.begin(12/*CS port*/)) {
      Serial.println("HSD Error");
      a++;
      if (a<=5) return;
    }
    else {
      statusForBluetooth = "E";
    }


  // RTC Setup
    if (! rtc.begin()) {
      Serial.println("HRTC Error");
    }
    
  //--------------------------board check----------------------------
//    boardCheck();

  // ----------------------Name a file name------------------
    if (RTCS){
      fileName = (dt.year()+'/'+dt.month()+'/'+dt.day()+".TXT");
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

    if (statusForBluetooth == "") statusForBluetooth = "=";
}
