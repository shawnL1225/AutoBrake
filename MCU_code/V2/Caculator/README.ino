// -------------------------PORTS----------------------------------------
  //digital Ports
    // D2-11 -> Serial ports
    // D12 -> brake permission
    
  //Communication
    //------------======= Serial10 brake [F] =======------------
      //--=== INPUT ===--
        // 'E' + brakeForce
      //--=== OUTPUT ===--
        // 'E' + brakeForce
        
    //------------======= Serial11 brake [B] =======------------
      //--=== INPUT ===--
        // 'D' + brakeForce
      //--=== OUTPUT ===--
        // 'D' + brakeForce
        
    //------------======== Serial12 Xavier [N]=======------------
      //--=== INPUT ===--
        //
      //--=== OUTPUT ===--
        //'F' + F_1 + F_2 + F_3
        
    //------------======== Serial13 distance [F] =======------------
      //--=== INPUT ===--
        //'F' + F_1 + ' ' + F_2 + ' '  + F_3
      //--=== OUTPUT ===--
        
    //-----------========= Serial4 Mother [A] =======------------
      //--=== INPUT ===--
        //'A' + '1/0' -> 1 is front distance is required / 0 is not required
        //'I' + riseAngle
        //'V' + nowSpeed
        //'E' + frontBrakeForce
        //'D' + backBrakeForce
      //--=== OUTPUT ===--
        //'E' + frontBrakeForce
        //'D' + backBrakeForce
        //'F' + F_1 + F_2 + F_3

        
