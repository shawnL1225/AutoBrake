// -------------------------PORTS----------------------------------------
  //digital Ports
    // D2-11 -> Serial ports
    // D12 -> brake permission
  //Communication
    //------------======= Serial1 brake [F] =======------------
      //--=== INPUT ===--
        // 'E' + brakeForce
      //--=== OUTPUT ===--
        // 'E' + brakeForce
    //------------======= Serial2 brake [B] =======------------
      //--=== INPUT ===--
        // 'D' + brakeForce
      //--=== OUTPUT ===--
        // 'D' + brakeForce
    //------------======== Serial3 Xavier =======------------
      //--=== INPUT ===--
        //
      //--=== OUTPUT ===--
        //
    //------------====== Serial4 distance [F] =======------------
      //--=== INPUT ===--
        //
      //--=== OUTPUT ===--
        //'A' + '1/0' -> 1 is front distance is required / 0 is not required
    //-----------======= Serial5 Mother [F] =======------------
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
