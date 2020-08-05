// -------------------------PORTS----------------------------------------
    //--------analogRead------------
      // A1 -> IR1080 1 
      // A2 -> IR1080 2
      
    //-------digitalRead----------
      //D3 -> ultraRright Trigger Pin
      //D2 -> ultraRight Echo Pin
      //D8 -> ultraMiddle Trigger Pin
      //D7 -> ultraMiddle Echo Pin
      //D11 -> ultra Left Trigger Pin
      //D12 -> ultraLeft Echo Pin
      //D4,5 -> communication
  
    //Communication
      //Serial4 -> Central   (4,5)*RX/TX*
      
       // --Code symbol for Serial4 (O)--
        //'R d' -> ultraRD + IRD80_1 + ultraMD + IRD80_2 + ultraLD
        //RS -> Right side has car
        
      // --Code symbol for Serial1 (O)--
        //'A' + '1/0' -> 1 is all distance is required / 0 is not required
        
