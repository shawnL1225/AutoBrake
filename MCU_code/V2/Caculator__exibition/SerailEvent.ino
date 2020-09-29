void SerialEvent() {
  if (Serial.available()) {
    char in = Serial.read();
    if (in == 'A') {
      char inA = Serial.read();
      FDR = bool(inA);
    }
    else if (in == 'E') {
      frontBrakeForce = Serial.parseInt();
      Serial.print('E');
      Serial.println(frontBrakeForce);
      Serial10.print('E');
      Serial10.print(frontBrakeForce);
      Serial10.print(' ');
    }
    else if (in == 'D') {
      backBrakeForce = Serial.parseInt();
      Serial.print('D');
      Serial.println(backBrakeForce);
      Serial11.print('D');
      Serial11.print(backBrakeForce);
      Serial11.print(' ');
    }
    else if (in == 'V') {
      nowSpeed = Serial.parseFloat();
      Serial.print('V');
      Serial.println(nowSpeed);
    }
  }

  Serial4.listen();
  delay(10);
  Serial4.listen();
  if (Serial4.available()) {
    char in = Serial4.read();
    if (in == 'A') {
      char inA = Serial4.read();
      FDR = bool(inA);
    }
    else if (in == 'V') {
//      Serial.println("IN");
      nowSpeed = Serial4.parseFloat();
      Serial.print('V');
      Serial.println(nowSpeed);
    }
    else if (in == 'E') {
      frontBrakeForce = Serial4.parseInt();
      Serial.print('E');
      Serial.println(frontBrakeForce);
      Serial10.print('E');
      Serial10.print(frontBrakeForce);
      Serial10.print(' ');
    }
    else if (in == 'D') {
      backBrakeForce = Serial4.parseInt();
      Serial.print('D');
      Serial.println(backBrakeForce);
      Serial11.print('D');
      Serial11.print(backBrakeForce);
      Serial11.print(' ');
    }
  }
  
  Serial10.listen();
  delay(10);
  Serial10.listen();
  if (Serial10.available()) {
    char in = Serial10.read();
    if (in == 'E') {
      frontBrakeForce = Serial10.parseInt();;
      Serial.print('E');
      Serial.println(frontBrakeForce);
//      Serial4.print('E');
//      Serial4.print(frontBrakeForce);
//      Serial4.print(' ');
    }
  }
  
  Serial11.listen();
  delay(10);
  Serial11.listen();
  if (Serial11.available()) {
    char in = Serial11.read();
    if (in == 'D') {
      backBrakeForce = Serial11.parseInt();;
      Serial.print('D');
      Serial.println(backBrakeForce);
//      Serial4.print('D');
//      Serial4.print(backBrakeForce);
//      Serial4.print(' ');
    }
  }

//  if (front_dist < 500) {
//    Serial12.println("<");//To XAVIER
//  }
//  Serial12.listen();
//  delay(10);
//  Serial12.listen();
//  if (Serial12.available()) {
//    char inbox = Serial12.read();
//    switch (inbox) {
//      case 'V':
//        //Front Vehicle Type
//        //0:No Data
//        //1:person/bicycle/motorbike
//        //2:car
//        //3:truck/bus
//        VehicleType = Serial12.parseInt();
//        break;
//      case 'R':
//        //Traffic Light : RED
//        Serial4.println("R");
//        break;
//      case 'D':
//        //Division
//        Serial4.println("D");
//        break;
//    }
//  }


  Serial13.listen();
  delay(10);
  Serial13.listen();
  if (Serial13.available()) {
//    Serial.println("From Dist Board");
    char in = Serial13.read();
    Serial.println(in);
    if (in == 'F') {
      front_dist = Serial13.parseInt();
      Serial.println("F : " + String(front_dist));
      if (FDR) {
//        Serial4.print('F');
//        Serial4.println(front_dist);
      }
    }
  }
}
