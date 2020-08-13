void SerialEvent() {
  if (Serial.available()) {
    char in = Serial.read();
    Serial.print(in);
    if (in == 'E') {
      int inD = Serial.parseInt();
      Serial.println(inD);
      int i = 0;
      while (i < 100) {
        Serial4.print('E');
        Serial4.println(inD);
        i++;
      }
    }
  }

  Serial4.listen();
  delay(10);
  Serial4.listen();
  if (Serial4.available()) {
    //    Serial.println("IN");
    char in = Serial4.read();
    //    Serial.println(in);
    if (in == 'A') {
      char inA = Serial4.read();
      A_F = bool(inA);
    }
    else if (in == 'V') {
      int inV = Serial4.parseInt();
      Serial.print('V');
      Serial.println(inV);
    }
    else if (in == 'E') {
      int backBrakeForce = Serial4.parseInt();
      Serial.print('E');
      Serial.print(backBrakeForce);
      Serial10.print('E');
      Serial10.print(backBrakeForce);
      Serial10.print(' ');
    }
    else if (in == 'D') {
      int frontBrakeForce = Serial4.parseInt();
      Serial.print('D');
      Serial.print(frontBrakeForce);
      Serial11.print('D');
      Serial11.print(frontBrakeForce);
      Serial11.print(' ');
    }
  }
  Serial10.listen();
  delay(10);
  Serial10.listen();
  if (Serial10.available()) {
    char in = Serial10.read();
    if (in == 'E') {
      int backBrakeForce = Serial10.parseInt();;
      Serial.print('E');
      Serial.println(backBrakeForce);
      Serial4.print('E');
      Serial4.print(backBrakeForce);
      Serial4.print(' ');
    }
  }
  Serial11.listen();
  delay(10);
  Serial11.listen();
  if (Serial11.available()) {
    char in = Serial11.read();
    if (in == 'D') {
      int frontBrakeForce = Serial11.parseInt();;
      Serial.print('D');
      Serial.print(frontBrakeForce);
      Serial4.print('D');
      Serial4.print(frontBrakeForce);
      Serial4.print(' ');
    }
  }


  if (front_dist < 500) {
    Serial12.println("<");//To XAVIER
  }
  Serial12.listen();
  delay(10);
  Serial12.listen();
  if (Serial12.available()) {
    char in = Serial12.read();
    if (in == 'N') {
      char inbox = Serial12.read();
      switch (inbox){
        case 'V':
          //Front Vehicle Type
          //0:No Data
          //1:person/bicycle/motorbike
          //2:car 
          //3:truck/bus
          VehicleType = Serial12.parseInt();
          break;         
        case 'R':
          //Traffic Light : RED
          Serial4.println("R");
          break;
        case 'D':
          //Division
          Serial4.println("D");
          break;
          
      }
    }
  }


  Serial13.listen();
  delay(10);
  Serial13.listen();
  if (Serial13.available()) {
    char in = Serial13.read();
    if (in == 'F') {
      int F1 = Serial13.parseInt();
      if (A_F) {
        Serial4.print('F');
        Serial4.println(F1);
      }
    }
  }
}
