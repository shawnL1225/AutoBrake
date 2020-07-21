void show (){
//  String printS = String(ultraLD) + "cm  \t" + String(ultraMD) + "cm  \t" + String(ultraRD) + "cm  \n" + String(IRD80_1) + "cm  \t" + String(IRD150) + "cm  \t"  + String(IRD80_2) + "cm  \t" ;
//  Serial.println(printS);
//  Serial.println("----------------------------------------");
  if (IRD80_1>50) IRD80_1 = ultraMD;
  if (IRD80_2>50) IRD80_2 = ultraMD;
  String send = "R " +String(ultraRD) +' '+  String(IRD80_2) + ' ' + String(ultraMD) + ' ' + String(IRD80_1) + ' '+  String(ultraLD)+ " " ;
  String send2 = String(BultraRD||BultraLD)+"\t"+String(BultraMD)+"\t"+String(BIRD80_1||BIRD80_2)+"\t";
//  delay(10);
  Serial.println(send);
  Serial.print(send2);
  if (Serial4.available()){
    Serial4required = bool (Serial.parseInt());
  }
  if (Serial4required){
    Serial4.println(send);
  }
  delay(100);
//  Serial.println("========================================");
}
