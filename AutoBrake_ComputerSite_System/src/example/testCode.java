package example;

import java.text.SimpleDateFormat;
import java.util.Date;

public class testCode {
    public static void main(String[] args) {
      SimpleDateFormat time = new SimpleDateFormat("yyyy,MM,dd HH:mm:ss.SSS");
      Date current = new Date();
      System.out.println(time.format(current));
      String timeS = time.toString();
      String send = "?"+ timeS ;
      System.out.println(send);
    }
}