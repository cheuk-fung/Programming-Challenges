import java.util.*;

public class A {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        String[] s = cin.next().split("WUB");
        for (String t : s) {
            if (t.compareTo("") != 0) System.out.print(t + " ");
        }
        System.out.println();
    }
}
