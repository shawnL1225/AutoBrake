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
    
  //------------------===== SD Check ====-------------
    randomSeed(analogRead(A1));
    int a = 0;
    if (!SD.begin(4/*CS port*/)) {
      Serial.println("SD err <I>");
      a++;
      if (a<=5) return;
      else {
        statusForBluetooth = "E";
      }
    }
    
    //--------------------------board check----------------------------
    Serial.print("?A");
    if (digitalRead(34)) Serial.print("?R");
    if (digitalRead(35)) Serial.print("?L");
    if (digitalRead(36)) Serial.print("?C");
    if (digitalRead(37)) Serial.print("?S");
    if (digitalRead(38)) Serial.print("?Z");
    else statusForBluetooth = 'E';
    if (digitalRead(39)) Serial.print("?X");
    else statusForBluetooth = 'E';
    if (digitalRead(40)) Serial.print("?T");

    // ----------------------Name a file name------------------
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

    if (statusForBluetooth == "") statusForBluetooth = "=";
}
