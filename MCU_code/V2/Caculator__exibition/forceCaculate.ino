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
    Serial.println("Brake START");
    for(int i = 0; i<3 ; i++) {
      Serial4.println(" Z");
      Serial4.flush();
    }
    digitalWrite(A3,1);
    delay(100);
    digitalWrite(A3,0);
    digitalWrite(A0,0);
//    Serial10.print('E');
//    Serial10.println(RBF);
    Serial11.print('D');
    Serial11.println(RFF_1);
    Serial11.flush();
    digitalWrite(10,1);
    delay(3000);
    Serial11.print('D');
    Serial11.println(RFF_2);
    Serial11.flush();
    times++;
    brake = 1;
  }
  if (abs(backBrakeForce -RFF_2)&&brake) {
    brakeF = 1;
    brake = 0;
  }
  if (nowSpeed <1&&brakeF) {
    Serial11.println("D0");
    brakeF = 0;
    delay(1000);
    digitalWrite(10,0);
  }
}
