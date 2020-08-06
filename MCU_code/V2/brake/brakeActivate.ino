void brakeA(){
  autoB = map(analogRead(A2), autoBMin, autoBMax, autoBMinF, autoBMaxF);
  manualB = map(analogRead(A3), manualBMin, manualBMax, manualBMinF, manualBMaxF);
  Serial.print("autoBrake : ");
  Serial.print(autoBF);
  Serial.print("\tmanualBrake : ");
  Serial.println(manualBF);
  TbrakeF = autoBF + manualBF;
}
