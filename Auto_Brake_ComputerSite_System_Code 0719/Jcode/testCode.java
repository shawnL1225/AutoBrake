package example;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class testCode {
    public static void main(String[] args) throws IOException {
        BufferedReader BFR = new BufferedReader (new InputStreamReader(System.in));
        Scanner sc = new Scanner(System.in);
        System.out.println("!@#$%^&*");
        int acsii = sc.next().charAt(0);
        System.out.println(acsii);
        int acsii1 = sc.next().charAt(0);
        System.out.println(acsii1);
        char ina = (char)acsii;
        System.out.println(ina);
        int a =0;
        a = sc.nextInt();
        System.out.println(a);
        int b =0;
        b = sc.nextInt();
        System.out.println(b);
    }
}