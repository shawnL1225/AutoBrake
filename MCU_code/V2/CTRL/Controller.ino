void CTRL(){
  // get value from controller [controller value]
    int valueFromController=analogRead(A1);                   //value could be from 0~1023, normal value should be within 180~880
    CTRLP = map(valueFromController,177,880,0,100);   //turn analogvalue to servo degree
    if (CTRLP<0) CTRLP =0;
    if (CTRLP != LCTRLP){
      Serial.print("X");
      Serial.println(CTRLP);
      Serial4.print("X");
      Serial4.print(CTRLP);
<<<<<<< HEAD
      Serial.print("X");
      Serial.print(CTRLP);
      LCTRLP = CTRLP;
=======
      Serial4.print(' ');
      CTRLP = LCTRLP;
>>>>>>> f73dc2aca2235564452727b1c9a29f28f170df8c
    }
    
  //Take botton be press on the controller
    if (!digitalRead(8)) {
      Serial.println("Button was Pressed");
      Serial4.write("^ ");
    }
}
