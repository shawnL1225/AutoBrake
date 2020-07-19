//------------------------SDWrite---------------------
  void SDWrite(String a){
      file = SD.open(fileName,FILE_WRITE);
      unsigned long msec= millis();
      int sec=0,mi=0,hr=0;
      if (msec%1000>=0){
        sec=msec/1000;
        msec=msec-1000*sec;
        
        if (sec%60>=0){
          mi=sec/60;
          sec=sec-mi*60;
          
          if (mi%60>=0){
            hr=mi/60;
            mi=mi-hr*60;
          }
        }
      }
      
      int fhr = hr + fixhr;
      int fmi = mi + fixmi;
      int fsec = sec + fixsec;
      int fmsec = msec + fixmsec;
      
      if (fmsec>=1000){
        fsec++;
        fmsec-=1000;
        if (fsec>=60){
          fmi++;
          fsec-=60;
          if (fmi>60){
            fhr++;
            fmi-=60;
          }
        }
      }
      
      //Print
      if (fhr==0) file.print("00");
      else if (fhr<10) {
        file.print("0");
        file.print(fhr);
//        Serial.print("0");
//        Serial.print(fhr);
      }
      else {
        file.print(fhr);
//        Serial.print(fhr);
      }
      
      file.print(":");
//      Serial.print(":");
      
      if (fmi==0) {
        file.print("00");
//        Serial.print("00");
      }
      else if (fmi<10) {
        file.print("0");
        file.print(fmi);
//        Serial.print("0");
//        Serial.print(fmi);
      }
      else {
        file.print(fmi);
  //      Serial.print(fmi);
      }
      
      file.print(":");
//      Serial.print(":");
          
      if (fsec==0) {
        file.print("00");
//        Serial.print("00");
      }
      else if (fsec<10) {
        file.print("0");
        file.print(fsec);
//        Serial.print("0");
//        Serial.print(fsec);
      }
      else {
        file.print(fsec);
//        Serial.print(fsec);
      }
      
      file.print(".");
//      Serial.print(".");
      
      if (fmsec==0) {
        file.print("00");
//        Serial.print("00");
      }
      else if (fmsec<10) {
        file.print("00");
        file.print(fmsec);
//        Serial.print("00");
//        Serial.print(fmsec);
      }
      else if (fmsec<100) {
        file.print("0");
        file.print(fmsec);
//        Serial.print("0");
//        Serial.print(fmsec);
      }
      else {
        file.print(fmsec);
//        Serial.print(fmsec);
      }
      
      file.print(" ->  ");
//      Serial.print(" ->  ");
      file.println(a);
      file.close();
  }
