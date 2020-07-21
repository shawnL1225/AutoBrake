void CTRL(){
  // get value from controller [controller value]
    int valueFromController=analogRead(A0);                   //value could be from 0~1023, normal value should be within 180~880
    CTRLP = map(valueFromController,190,880,0,100);   //turn analogvalue to servo degree
    if (CTRLP<5) CTRLP = 0;
    if (!motorper&&CTRLP != LCTRLP||CTRLP==0) {
      Serial1.print("M0|");
      Serial.println("M0");
      CTRLP = LCTRLP;
      delay(50);
    }
    else if (motorper&&CTRLP != LCTRLP){
      if (LCTRLP<CTRLP){
        for (int a = LCTRLP ; a < CTRLP ; a+=5){
          Serial1.print("M");
          Serial1.print(a);
          Serial1.print('|');
          Serial.print("M");
          Serial.println(a);
          delay(50);
        }
      }
      if (LCTRLP>CTRLP){
        for (int a = LCTRLP ; a > CTRLP ; a-=5){
          Serial1.print("M");
          Serial1.print(a);
          Serial1.print('|');
          Serial.print("M");
          Serial.println(a);
          delay(50);
        }
      }
      CTRLP = LCTRLP;
    }
    Serial1.print('T');
    Serial1.print(random(25,28));
    Serial1.print('|');
    Serial1.print("B90|");
    delay(50);
}
