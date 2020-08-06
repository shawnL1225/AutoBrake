void brakeS(){
  autoBF = map(analogRead(A2), autoBMin, autoBMax, autoBMinF, autoBMaxF);
  manualBF = map(analogRead(A3), manualBMin, manualBMax, manualBMinF, manualBMaxF);
  TbrakeF = autoBF + manualBF;
  Serial.print("autoBrake Force : ");
  Serial.print(autoBF);
  Serial.print(" N\tManual Brake : ");
  Serial.print(manualBF);
  Serial.print(" N\tTotal Force : ");
  Serial.print(TbrakeF);
  Serial.println(" N");
}
