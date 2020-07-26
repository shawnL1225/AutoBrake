void STATE() {
  String inS="";
  Serial1.println("AT+STATE");
  while (Serial1.available()<0);
    char in = Serial1.read();
    if (in=='+'){
      while(Serial1.available()){
        char iin = Serial1.read();
        inS += iin;
      }
    }
    inS.replace("OK","");
    inS.replace("\n","");
    inS.replace("STATE","");
    inS.replace(":","");
    inS.replace("=","");
    inS.replace(" ","");

  if (inS.length()>3){
    char a3 = inS[3];
    if (a3 =='T') bluetoothStatus = 0; //INITIALIZING
    else if (a3 =='D') bluetoothStatus = 1; //READY
    else if (a3 =='U') bluetoothStatus = 2; //INQUIRING 
    else if (a3 =='R') bluetoothStatus = 3; //PAIRABLE 
    else if (a3 =='N') {
      char a8 = inS[8];
      if (a8 =='N') bluetoothStatus = 4; //CONNECTING
      else if (a8 =='D') bluetoothStatus = 5; //CONNECTED
    }
  }
  else bluetoothStatus = inS.toInt();

  if (bluetoothStatus!=6) digitalWrite(MP,0);

  Serial.print("W");
  Serial.print(bluetoothStatus);
  Serial.println("");
}
