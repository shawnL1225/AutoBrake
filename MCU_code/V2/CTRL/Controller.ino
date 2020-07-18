void CTRL(){
  // get value from controller [controller value]
    int valueFromController=analogRead(A1);                   //value could be from 0~1023, normal value should be within 180~880
    CTRLP = map(valueFromController,182,880,0,100);   //turn analogvalue to servo degree
    if (CTRLP != LCTRLP){
      Serial4.print("B");
      Serial4.print(CTRLP);
      CTRLP = LCTRLP;
    }
    
  //Take botton be press on the controller
    if (!digitalRead(8)) {
      Serial.println("Button was Pressed");
      Serial4.write("^ ");
    }
}
