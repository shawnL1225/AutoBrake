void OLEDwc(){
  if (in == 1){
    in = 2;
    screen.clearDisplay();
    screen.setCursor(0, 15); // (x,y)
    screen.setFont(&FreeSans9pt7b);
    screen.println("Please Select :");
    screen.println("1. Get Voltage");
    screen.setFont(&FreeSansBold9pt7b);
    screen.println("2. Charge\n");
    screen.display();
    buzzer(50,1);
    delay(500);
  }
  else if (in == 2){
    in = 1;
    screen.clearDisplay();
    screen.setCursor(0, 15); // (x,y)
    screen.setFont(&FreeSans9pt7b);
    screen.println("Please Select :");
    screen.setFont(&FreeSansBold9pt7b);
    screen.println("1. Get Voltage");
    screen.setFont(&FreeSans9pt7b);
    screen.println("2. Charge\n");
    screen.display();
    buzzer(50,1);
    delay(500);
  }
}
