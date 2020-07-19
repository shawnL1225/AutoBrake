void setup() {
  // begin
  Serial.begin(9600);
  Serial1.begin (9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial4.begin(9600);
  Serial5.begin(9600);
  Serial6.begin(9600);
  Serial7.begin(9600);
  Serial8.begin(9600);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial1.setTimeout(100);
  Serial2.setTimeout(100);
  Serial3.setTimeout(100);
  Serial4.setTimeout(100);
  Serial5.setTimeout(100);
  Serial6.setTimeout(100);
  Serial7.setTimeout(100);
  Serial8.setTimeout(100);
  
  //--------------------------board check----------------------------
    
  //------------------------===== SD Check ====-------------
    randomSeed(analogRead(A1));
    if (!SD.begin(4/*CS port*/)) {
      Serial.println("SD err <I>");
      Serial2.print("SI"); //Please insert SD Card
      a++;
      if (a<=5) return;
      else {
        statusForBluetooth = "SE";
      }
    }

    // Name a file name
    if (isAlphaNumeric(fileName[1])) ;
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
    Serial.println(fileName);
    }
    
  //------------------------Ready to strat---------------------------------
    Serial.println("Bike LOCK");
    Serial.println("START");
    if (statusForBluetooth == "") statusForBluetooth = "=";
}
