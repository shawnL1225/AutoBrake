void IR (){
  double IRD80_1_ave_distance_cm=0, IRD80_2_ave_distance_cm=0;
  
  IRD80_1_ave_distance_cm += IR80_1.distance();

  IRD80_2_ave_distance_cm += IR80_2.distance();

  IRD80_1_ave_distance_cm += 1.3;
  IRD80_2_ave_distance_cm += 1.3;
   
  IRD80_1 = IRD80_1_ave_distance_cm ;
  IRD80_2 = IRD80_2_ave_distance_cm ;
}
