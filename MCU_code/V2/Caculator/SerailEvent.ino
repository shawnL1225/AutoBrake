void SerialEvent(){
  if (Serial4.available()){
    char in = Serial4.read();
    switch (in){
      case('A'):{
        char inA = Serial.read();
        A_F = bool(inA);
      }
      case('I'):{
        char inI =Serial.read();
      }
      case('V'):{
        char inV =Serial.read();
      }
      case('E'):{
        char inE =Serial.read();
        int backBrakeForce = Serial4.parseInt();
        Serial.print('E');
        Serial.print(backBrakeForce);
        Serial10.print('E');
        Serial10.print(backBrakeForce);
        Serial10.print(' ');
      }
      case('D'):{
        int frontBrakeForce = Serial4.parseInt();
        Serial.print('D');
        Serial.print(frontBrakeForce);
        Serial11.print('D');
        Serial11.print(frontBrakeForce);
        Serial11.print(' ');
      }
    }
  }
  if (Serial10.available()){
    char in = Serial10.read();
    if (in == 'E'){
      int backBrakeForce = Serial10.parseInt();;
      Serial.print('E');
      Serial.println(backBrakeForce);
      Serial4.print('E');
      Serial4.print(backBrakeForce);
      Serial4.print(' ');
    }
  }
  if (Serial11.available()){
    char in = Serial11.read();
    if (in == 'D'){
      int frontBrakeForce = Serial11.parseInt();;
      Serial.print('D');
      Serial.print(frontBrakeForce);
      Serial4.print('D');
      Serial4.print(frontBrakeForce);
      Serial4.print(' ');
    }
  }
  if (Serial12.available()){
    char in = Serial12.read();
    switch(in){
      case('X'):{
        ;
      }
    }
  }
  if (Serial13.available()){
    char in = Serial13.read();
    if (in == 'F'){
      float F1 = Serial13.parseFloat();
      float F2 = Serial13.parseFloat();
      float F3 = Serial13.parseFloat();
      if (A_F){
        Serial4.print('F');
        Serial4.print(' ');
        Serial4.print(F1);
        Serial4.print(' ');
        Serial4.print(F2);
        Serial4.print(' ');
        Serial4.print(F3);
      }
      /*Xavier COMM*/
    }
  }
}
