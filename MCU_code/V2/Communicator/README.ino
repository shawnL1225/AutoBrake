// -------------------------PORTS----------------------------------------
  //Communication
    // -----Serial1 (motor_with_battery_brakeD_CTRL)---------
    // --Code symbol for Serial1 (I)--
      //'@' <UNLOCK>
      //'%' <LOCK>
    // --Code symbol for Serial1 (O)--
      //'P'+ASPXpower
      //'^' <Button Pressed>
      //'V'+batteryV <Actual Voltage *100>
      //'#' <Brake applied>
      //'E' <CTRL　Error　Occur>
      //'S' <CTRL Error Solved>
      //
    
    // -----Serial2 (cellphone)----------
    // --Code symbol for Serial2 (I)--
      //'@'+YY+MM+DD+HH+MM+SS+MsMsMs
    // --Code symbol for Serial2 (O)--
      //'S'+Speed
      //'B'+BVB
      //'M'+RASPXpowerR 
      //'T'+Temp
      //'W'
      //'L'```````
      //'R'
      

    // -----Serial3 (Speed Sensor)----------
    // --Code symbol for Serial3 (I)--
      // 'V' + hv
      // 'E' <Error Occur>
    // --Code symbol for Serial3 (O)--
      
    
    
