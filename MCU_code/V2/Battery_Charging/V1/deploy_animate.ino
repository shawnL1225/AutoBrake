void depani(){
  screen.clearDisplay();
  screen.setCursor(0,20); // (x,y)
  screen.println("     Procedure\n     Launched");
  screen.display();
  delay(100);
  screen.setCursor(54,55); // (x,y)
  Serial.print('.');
  screen.setFont(&FreeSans12pt7b);
  screen.print(".");
  screen.display();
  delay(100);
  Serial.print('.');
  screen.print(".");
  screen.display();
  delay(100);
  Serial.println('.');
  screen.print(".");
  screen.display();
}
