// -------------------------PORTS----------------------------------------
  //digital Ports
    // D33 -> motor permission to CTRL digital Pin 7
    // D34 -> distance sensor [R]
    // D35 -> distance sensor [L]
    // D36 -> distance sensor [B]
    // D37 -> speed sensor
    // D38 -> caculation board
    // D39 -> CTRL
    // D40 -> heat n Gsensorg
  
  //Communication
/**/// -----=========Serial (deskopSite)======---------
    // --Code symbol for Serial (O)--
      //'?' + charOfMCU -> status
      //'@' -> Enable
      //'#' -> Disable
      //'X' + CTRLP 
      //'V' + nowSpeed 
      //'T' + motorTemp 
      //'G' + tiltAngle
      //'I' + riseAngle
      //'A' + vichileAcc
      //'B' + BatteryP
      //'E' + frontBrakeForce
      //'D' + backBrakeForce
      //'H' + motherBoardSerial
      //'N' + NXTSerial
      //'F' + F_1 + F_2 + F_3
      //'L' + L_1 + L_2 + L_3 + L_4 + L_5
      //'R' + R_1 + R_2 + R_3 + R_4 + R_5
      //'C' + C_1 + C_2 + C_3 
    // --Code symbol for Serial (I)--
      //'@' -> Enable
      //'#' -> Disable
      //'M' + CTRLP
      //'A' + '1/0' -> 1>>require distance
      //'?' -> request for now status
      //"$C" -> connected
      //"$D" -> disconnected
      //'E' + frontBrakeForce
      //'D' + backBrakeForce
      //'H' + mother board Serial
      //'N' + NXT board Serial
      
    // -----=========Serial1 (bluetooth)======---------
    // --Code symbol for Serial1 (I)--
      //'?' -> request for now status
      //'@' -> motor permited
      //'#' -> motor not permited
    // --Code symbol for Serial1 (O)--
      //'S' + speed 
      //'B' + batteryPercentage
      //'M' + motorPercentage
      //'T' + motorTemperature
      //'X' -> Red Light warning 
      //'Y' -> vechile devious
      //'Z' + '1/0' + 'f/r/l/b' -> distance under limited 
     //----------===== start status =====---------
      //'=' -> System All Set
      //"SC" -> SD Checking
      //"SO" -> SD OK
      //"SE" -> SD Error
      //"CC" -> CTRL Checking
      //"CO" -> CTRL OK
      //"CE" -> CTRL Error


    // -----=========Serial2 (distance [R]<R>)|34|======---------
    // --Code symbol for Serial2 (I)--
      //'R' -> ultraRD + IRD80_1 + ultraMD + IRD80_2 + ultraLD
      //RS -> Right side has car
    // --Code symbol for Serial2 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

    // -----=========Serial3 (distance [L]<L>)|35|======---------
    // --Code symbol for Serial3 (I)--
      //'L' -> ultraLD + IRD80_2 + ultraMD + IRD80_1 + ultraRD
      // LS -> Left side has car
    // --Code symbol for Serial3 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

/**/// -----=========Serial4 (distance [B]<C>)|36|======---------
    // --Code symbol for Serial4 (I)--
      //'C' -> ultraLD + IRD80_2 + ultraMD + IRD80_1 + ultraRD
      // CS -> Left side has car
    // --Code symbol for Serial4 (O)--
      //'A' + '1/0' -> 1 is all distance is required / 0 is not required

    // -----=========Serial5 (SpeedSensor <S>)|37|======---------
    // --Code symbol for Serial5 (I)--
      // 'V' + hv
      // 'E' <Error Occur>
    // --Code symbol for Serial5 (O)--

    // -----=========Serial6 (Caculation <Z>)|38|======---------
    // --Code symbol for Serial6 (I)--
      //'E' + frontBrakeForce
      //'D' + backBrakeForce
      //'F' + F_1 + F_2 + F_3
    // --Code symbol for Serial6 (O)--
      //'A' + '1/0' -> 1 is front distance is required / 0 is not required
      //'I' + riseAngle
      //'V' + nowSpeed

    // -----=========Serial7 (CTRL <X>)|39|======---------
    // --Code symbol for Serial7 (I)--
      //'X' + CTRLP
      //'^' -> Button Pressed
      //'B' + batteryV <Actual Voltage *100>
    // --Code symbol for Serial7 (O)--
      //'V' + nowSpeed 
      //'X' + CTRLP
    //digitalPin 
      //D41 -> motor permission

    // -----=========Serial8 (Heat n Gsensor <T>)|40|======---------
    // --Code symbol for Serial8 (I)--
      //'G' -> Tilt Angle
      //'I' -> Rise Angle
      //'A' -> acceleratiom
      //'T' -> motor temperatrue
      //'t' -> Temperature for sound
      //'h' -> Humidity for sound
    // --Code symbol for Serial8 (O)--
    

      
      
    
    
