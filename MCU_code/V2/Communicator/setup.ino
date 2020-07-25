void setup() {
  // begin
  Serial.begin(9600);
  Serial1.begin (9600);
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

  for (int i =34;i<=46;i++) pinMode(i,INPUT);
  
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
    if (digitalRead(S2)) Serial.print("?R");
    if (digitalRead(S3)) Serial.print("?L");
    if (digitalRead(S4)) Serial.print("?C");
    if (digitalRead(S5)) Serial.print("?S");
    if (digitalRead(S9)) Serial.print("?P");
    if (digitalRead(S7)) Serial.print("?X");
    else statusForBluetooth = 'E';
    if (digitalRead(S8)) Serial.print("?T");
    if (digitalRead(S9)) Serial.print("?Z");
    else statusForBluetooth = 'E';
    if (digitalRead(S10)) Serial.print("?D");
    if (digitalRead(S11)) Serial.print("?E");
    if (digitalRead(S12)) Serial.print("?N");
    else statusForBluetooth = 'E';
    if (digitalRead(S13)) Serial.print("?F");
    

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
