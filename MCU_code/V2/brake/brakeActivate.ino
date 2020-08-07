void brakeA(int requestForce){
  if (requestForce>TbrakeF){
    digitalWrite(6,1);
    while (requestForce>TbrakeF){
    brakeS();
      if (TbrakeF>=requestForce){
        digitalWrite(6,0);
        break;
      }
    }
    
    if (TbrakeF>=requestForce){
      digitalWrite(6,0);
    }
  }
  
  else if (requestForce<TbrakeF){
    digitalWrite(5,1);
    while (requestForce<TbrakeF){
    brakeS();
      if (TbrakeF<=requestForce){
        digitalWrite(5,0);
        break;
      }
    }
    
    if (TbrakeF<=requestForce){
      digitalWrite(5,0);
    }
  }
}
