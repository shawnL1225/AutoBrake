void detect(){
  if ((BultraRD||BultraLD)&&BultraMD&&(BIRD80_1||BIRD80_2)){
    Serial4.println("LS");
    Serial.println("LS");
    BIRD80_1 = 0;
    BIRD80_2 = 0;
    BultraLD = 0;
    BultraMD = 0;
    BultraRD = 0;
  }
}
