package example;
public class testCode {
    public static void main(String[] args) {
        String line = "A123";
        line = line.replaceAll("A", "");
        System.out.println(line);
        int num = Integer.parseInt(line);
        System.out.println(num);
    }
}