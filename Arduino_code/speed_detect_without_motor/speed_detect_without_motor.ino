#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
 
int encoder = 2;
 
volatile unsigned int counter;
int rpm;
 
const int rs = 8, en = 3, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup() {
  Serial.begin(9600);
  pinMode(encoder, INPUT);
 
  digitalWrite(encoder, HIGH);

 
  attachInterrupt(0,countpulse,RISING);
  lcd.begin(16, 2);
}
 
void countpulse(){
        counter++;
}
 
void loop() {
  static uint32_t previousMillis;
  if (millis() - previousMillis >= 1000) {
            rpm = (counter/16)*60;          
            counter = 0;
            previousMillis += 1000;
  }
  Serial.print("Speed:  ");
  Serial.print( rpm);
  Serial.println(" rpm");
    
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  lcd.setCursor(7,0);
  lcd.print(rpm);
  lcd.print(" rpm");
  delay(1);
}
