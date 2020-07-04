void setup() {
  Serial.begin(9600);
  Serial2.begin (9600);
  Serial1.begin(9600);
  Serial3.begin(9600);
  Serial.setTimeout(100);
  Serial2.setTimeout(100);
  Serial1.setTimeout(100);
  Serial3.setTimeout(100);
  pinMode(38,OUTPUT);
  digitalWrite(22,0);
  digitalWrite(24,0);
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(39,INPUT_PULLUP);
  digitalWrite(38,0);

//  lcd.begin(16, 2);
  randomSeed(analogRead(A3));
  
  Serial.println("HPlease connect to the cepllphone");
  if (1){
    while (Serial1.available()==0&&Serial.available()==0) {
      lcd.setCursor(0,0);
      lcd.print("Pls Connect to");
      lcd.setCursor(0,1);
      lcd.print("Phone");
    }
    delay(1000);
    if(Serial1.available()) {
      char in =Serial1.read();
      if(in == '?') {
        unsigned long mtime= millis();
        int amsec=0,asec=0,ami=0,ahr=0;
        if (mtime%1000>0){
          asec=mtime/1000;
          amsec=mtime-1000*asec;
          if (asec%60>0){
            ami=asec/60;
            asec=asec-ami*60;
            if (ami%60>0){
              ahr=ami/60;
              ami=ami-ahr*60;
            }
          }
        }
        int year = Serial1.parseInt();
        int month = Serial1.parseInt();
        int date = Serial1.parseInt();
        int hr = Serial1.parseInt();
        fixhr = hr - ahr;
        int mi = Serial1.parseInt();
        fixmi = mi - ami;
        int sec = Serial1.parseInt();
        fixsec = sec - asec;
        int msec = Serial1.parseInt();
        int fixmsec = msec - asec;
        fileName = String(year)+'-'+String(month)+'-'+String(date)+".txt";
        lcd.clear();
        String dateS=String(year)+'/'+String(month)+'/'+String(date)+' ';
        String timeS=String(hr)+':'+String(mi)+':'+String(sec)+'.'+String(msec);
        lcd.setCursor(0,0);
        lcd.print(dateS);
        lcd.setCursor(0,1);
        lcd.print(timeS);
//        Serial.print(dateS);
//        Serial.println(timeS);
        delay(1000);
      }
    }
  }
  
  //--------------------------initialize----------------------------
  if (1){
    delay(50);
    lcd.setCursor(0,0); // set cursor at first line first alphabet
    lcd.print("Initializing");
    Serial.println("HInitializing");
    delay(100);
    lcd.print(".");
    delay(100);
    lcd.print(".");
    delay(100);
    lcd.println(".");
    delay(100);
    Serial.println("Hlcd OK");
    delay(500);
}
   
    Serial.println("?A ");
    delay(10);
    Serial.println("?N ");
    delay(10);
    Serial.println("?R ");
    delay(10);
    Serial.println("?S ");
    delay(10);
    Serial.println("?T ");
    delay(10);

   //Motor
    SPX1.attach(A7);
    SPX2.attach(A8);
    SPX(92);
    Serial.println("HBREAK STOP");
    
    Serial1.print("SO ");
   //Controller
    int valueFromController = analogRead(A0);
    int changedValueFromController = map(valueFromController, 180, 880, 93, 145);
    lcd.setCursor(0,1);
    lcd.print("             ");
    lcd.setCursor(0,1);
    lcd.print("CTRL");
    Serial1.print("CC ");
    delay(100);
    lcd.print('.');
    delay(100);
    lcd.print('.');
    if (changedValueFromController > 94) err = 1;
    if (err) {
      Serial.println("HController Err");
      
      Serial1.print("CE");
      lcd.print("err");
      delay(1000);
      lcd.setCursor(0,0);
      lcd.print("Pls RESTART");
      lcd.setCursor(0,1);
      lcd.print("If error keep occur contact to engineer");
      delay(100);
      lcd.scrollDisplayLeft();
      while (1){
        lcd.setCursor(0,0);
        lcd.print("Pls RESTART");
      }
    }
    else {
      Serial.println("HController Set ");
      SDWrite("Controller Set");
      Serial1.print("CO");
      lcd.print("SET");
      delay(500);
    }
    SPX(100);
    SPX(4);
    SPX(92);
   //delcare
    
    pinMode (3,INPUT);
    pinMode (8,INPUT_PULLUP);
    pinMode (VGALED,OUTPUT);
    digitalWrite(VGALED,0);
    delay(100);
    digitalWrite(VGALED,1);
    delay(100);
    digitalWrite(VGALED,0);
    appStart=0;
    
  //------------------------Ready to strat---------------------------------
    lcd.noBacklight();
    delay(250);
    lcd.backlight(); 
    delay(700);
    lcd.clear();
    delay(50);
    lcd.setCursor(0,1); 
    lcd.print("Speed ");
    lcd.print(hv);
    lcd.setCursor(9,1);
    lcd.print(" ");
    lcd.print("km/hr");
    lcd.setCursor(0,0);
    lcd.print("LOCK");
    Serial.println("HBike LOCK ");
    Serial.println("HSTART ");
    SDWrite("START");
    delay(50);
    Serial1.write("=");
    delay(500);
    Serial.print("B0 T20 S0 M0");
}
