void forceCaculate(){

//  float T = 4;
//
//  float Fbab = 0;
//  float Fbc = 0;
//  float Fbd = 0;
//
//  Fbab = 100*nowSpeed/T - 19.6133 - 0.301*nowSpeed*nowSpeed;
//  Fbc = (16.51 * nowSpeed + 323.815583 * riseAngle)/0.0711;
//  Fbd = 980.665 * riseAngle + 108*nowSpeed/t - 19.6133 - 0.301*nowSpeed*nowSpeed;
//
//  Serial.print("Fbab: ");
//  Serial.print(Fbab);
//  Serial.print("Fbc: ");
//  Serial.print(Fbc);
//  Serial.print("Fbd: ");
//  Serial.print(Fbd);

//--------------------experiment-------------------------
  if (!digitalRead(A1)) {
    digitalWrite(A3,1);
    delay(100);
    digitalWrite(A3,0);
  }
  if (nowSpeed >= expSetSpeed&&times<3&&(abs(RFF-frontBrakeForce)>5||abs(RBF-backBrakeForce)>5)||!digitalRead(A1)) brake = 1;
  else brake = 0;

  if (abs(RFF-frontBrakeForce)<5||abs(RBF-backBrakeForce)<5){
    Serial10.println("S ");
    Serial11.println("S ");
  }
  
  if (brake){
    digitalWrite(A0,0);
    Serial10.print('E');
    Serial10.println(RFF);
    Serial11.print('D');
    Serial11.println(RBF);
    Serial11.flush();
    Serial10.println("R1 L1");
    Serial11.println("R1 L1");
    Serial11.flush();
    times++;
    Serial.println("Brake START");
  }

  file = SD.open(fileName,FILE_WRITE);
  unsigned long msec= millis();
  int sec=0,mi=0;
  if (msec%1000>=0){
    sec=msec/1000;
    msec=msec-1000*sec;
    if (sec%60>=0){
      mi=sec/60;
      sec=sec-mi*60;
    }
  }
  String send = String(mi)+':'+String(sec)+'.'+String(msec)+"\tF: "+String(front_dist)+"\tS: "+String(nowSpeed)+"\tFB: "+String(frontBrakeForce)+"\tBB: "+String(backBrakeForce);
  file.println(send);
  file.close();
  
}
