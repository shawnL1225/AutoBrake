void CTRL(){
  // get value from controller [controller value]
    int valueFromController=analogRead(A1);                   //value could be from 0~1023, normal value should be within 180~880
    int SPXpower = map(valueFromController,182,880,93,145);   //turn analogvalue to servo degree

  // go to  motor loop
    motor(SPXpower, hv, brake);
    
  //Take botton be press on the controller
    if (!digitalRead(8)) {
      Serial.println("Button was Pressed");
      Serial4.write("^ ");
    }
}
