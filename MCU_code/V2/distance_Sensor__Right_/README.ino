// -------------------------PORTS----------------------------------------
    //--------analogRead------------
      // A1 -> IR1080 1 
      // A2 -> IR1080 2
      
    //-------digitalRead----------
      //D4 -> ultraRright Trigger Pin
      //D5 -> ultraRight Echo Pin
      //D6 -> ultraMiddle Trigger Pin
      //D7 -> ultraMiddle Echo Pin
      //D8 -> ultra Left Trigger Pin
      //D9 -> ultraLeft Echo Pin
      // D10,11 -> communication
  
    //Communication
      //Serial4 -> Central   (10,11)*RX/TX*
      
       // --Code symbol for Serial4 (O)--
        //'R' -> ultraRD + IRD80_1 + ultraMD + IRD80_2 + ultraLD
        //RS -> Right side has car
        
      // --Code symbol for Serial1 (O)--
        //'A' + '1/0' -> 1 is all distance is required / 0 is not required
        
