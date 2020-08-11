void detect(){
  if ((BultraRD||BultraLD)&&BultraMD&&(BIRD80_1||BIRD80_2)){
    Serial4.println("RS");
    Serial.println("RS");
    BIRD80_1 = 0;
    BIRD80_2 = 0;
    BultraLD = 0;
    BultraMD = 0;
    BultraRD = 0;
  }
}
