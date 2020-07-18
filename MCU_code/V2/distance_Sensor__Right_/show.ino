void show (){
//  String printS = String(ultraLD) + "cm  \t" + String(ultraMD) + "cm  \t" + String(ultraRD) + "cm  \n" + String(IRD80_1) + "cm  \t" + String(IRD150) + "cm  \t"  + String(IRD80_2) + "cm  \t" ;
//  Serial.println(printS);
//  Serial.println("----------------------------------------");
  if (IRD80_1>50) IRD80_1 = ultraMD;
  if (IRD80_2>50) IRD80_2 = ultraMD;
  String send = "R " +String(ultraRD) +' '+  String(IRD80_2) + ' ' + String(ultraMD) + ' ' + String(IRD80_2) + ' '+  String(ultraLD);
//  delay(10);
  Serial.println(send);
  Serial4.print(send);
  delay(100);
//  Serial.println("========================================");
}
