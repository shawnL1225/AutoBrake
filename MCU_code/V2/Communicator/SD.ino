//------------------------SDWrite---------------------
void SDWrite(String a){
    file = SD.open(fileName,FILE_WRITE);
    file.println(a);
    file.close();
}
