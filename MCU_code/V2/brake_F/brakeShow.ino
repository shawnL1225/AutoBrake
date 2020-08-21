void brakeS(){
  (void)analogRead(A2);
  autoBF = map(analogRead(A2), autoBMin, autoBMax, autoBMinF, autoBMaxF);
  delay(10);
  autoBF = map(analogRead(A2), autoBMin, autoBMax, autoBMinF, autoBMaxF);
  (void)analogRead(A3);
  manualBF = map(analogRead(A3), manualBMin, manualBMax, manualBMinF, manualBMaxF);
  delay(10);
  manualBF = map(analogRead(A3), manualBMin, manualBMax, manualBMinF, manualBMaxF);
  TbrakeF = autoBF + manualBF;
  if (Serial){
//    Serial.print("autoBrake Force : ");
//    Serial.print(autoBF);
//    Serial.print(" N\tManual Brake : ");
//    Serial.print(manualBF);
//    Serial.print(" N\tTotal Force : ");
//    Serial.print(TbrakeF);
//    Serial.println(" N");
    Serial.print('E');
    Serial.println(autoBF);
  }
}
