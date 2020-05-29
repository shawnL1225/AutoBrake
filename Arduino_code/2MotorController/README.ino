//--------------------------motor active list-------------------------------------
  //make SPX move from vslue "SPXpower"
  //~5 or 180~598    NON BREAK STOP
  //6~44             MAX REVERSE
  //45~90            REVERVE
  //91~94            BREAK　STOP
  //95~141           FORWARD
  //142~179          MAX FORWARD 

// -------------------------PORTS----------------------------------------
  //-------analogRead-----------
    // A0 -> controller
    // A7 -> SPX1
    // A8 -> SPX2
    // A10 -> brakeV
    
  //-------digitalRead----------
    // D3 -> VGA signal in
    // D4 -> CS port of SD card
    // D8 -> botton on the controller
    // D13 -> VGA successfully pulg in light 
    // D50~53 -> MISO *Do Not Plug Anything In*    

  //Communication
    // Serial1 -> relay
    // Serial2 -> Cellphone
    // Serial3 -> brake
    // I2C -> lcd
    // SPI -> SD Card
