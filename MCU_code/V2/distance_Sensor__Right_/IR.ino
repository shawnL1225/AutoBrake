void IR (){
  double IRD150_ave_distance_cm=0 , IRD80_1_ave_distance_cm=0, IRD80_2_ave_distance_cm=0;

  IRD80_1_ave_distance_cm += IR80_1.distance();
  if (IRD80_1<50) {
    BIRD80_1 = 1 ;
    trigger_time  = millis();
  }
  else if (trigger_time - millis()<3000) BIRD80_1 = 0 ;

  IRD80_2_ave_distance_cm += IR80_2.distance();
  if (IRD80_2<50) {
    BIRD80_2 = 1 ;
    trigger_time  = millis();
  }
  else if (trigger_time - millis()<3000) BIRD80_2 = 0 ;

  IRD80_1_ave_distance_cm += 1.3;
  IRD80_2_ave_distance_cm += 1.3;
   
  IRD80_1 = IRD80_1_ave_distance_cm ;
  IRD80_2 = IRD80_2_ave_distance_cm ;
}
