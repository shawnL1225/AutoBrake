// -------------------------PORTS----------------------------------------
  //Communication
    // -----=========Serial1 (bluetooth)======---------
    // --Code symbol for Serial1 (I)--
      //
    // --Code symbol for Serial1 (O)--
      //'S' + speed 
      //'B' + batteryPercentage
      //'M' + motorPercentage
      //'T' + mtorTemperature
      //'X' + 
      //'Y' + 
      //'Z' + 
     //----------===== start status =====---------
      //'=' -> System All Set
      //"SC" -> 
      //"SO" -> SD OK
      //"SE" -> SD Error
      //"CC" ->  
      //"CO" -> CTRL OK
      //"CE" -> CTRL Error

    // -----=========Serial2 (distance [R]<R>)======---------
    // --Code symbol for Serial1 (I)--
      //'R' -> ultraRD + IRD80_1 + ultraMD + IRD80_2 + ultraLD
      //RS -> Right side has car
    // --Code symbol for Serial1 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

    // -----=========Serial3 (distance [L]<L>)======---------
    // --Code symbol for Serial1 (I)--
      //'L' -> ultraLD + IRD80_2 + ultraMD + IRD80_1 + ultraRD
      // LS -> Left side has car
    // --Code symbol for Serial1 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

    // -----=========Serial4 (distance [B]<C>)======---------
    // --Code symbol for Serial1 (I)--
      //
    // --Code symbol for Serial1 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

    // -----=========Serial5 (SpeedSensor <S>)======---------
    // --Code symbol for Serial1 (I)--
      // 'V' + hv
      // 'E' <Error Occur>
    // --Code symbol for Serial1 (O)--

    // -----=========Serial6 (Caculation <Z>)======---------
    // --Code symbol for Serial1 (I)--
      //
    // --Code symbol for Serial1 (O)--
      //

    // -----=========Serial7 (CTRL <X>)======---------
    // --Code symbol for Serial1 (I)--
      //
    // --Code symbol for Serial1 (O)--
      //

    // -----=========Serial8 (Heat n Gsensor <T>)======---------
    // --Code symbol for Serial1 (I)--
      //'G' -> Tilt Angle
      //'I' -> Rise Angle
      //'A' -> acceleratiom
      //'t' -> Temperature for sound
      //'h' -> Humidity for sound
    // --Code symbol for Serial1 (O)--
    

      
      
    
    
