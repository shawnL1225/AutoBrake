//------------------------SDWrite---------------------
void SDWrite(String a){
  file = SD.open(fileName,FILE_WRITE);
  if (RTCS == 1){
    dt = rtc.now(); // read the time from the DS3231 RTC chip
    file.print(dt.year(), DEC);
    file.print('/');
    file.print(dt.month(), DEC);
    file.print('/');
    file.print(dt.day(), DEC);
    file.print(' ');
    file.print(dt.hour(), DEC);
    file.print(':');
    file.print(dt.minute(), DEC);
    file.print(':');
    file.print(dt.second(), DEC);
  }
  else file.print(millis());
  file.println(a);
  file.close();
}
