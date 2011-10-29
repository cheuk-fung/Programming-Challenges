/*
 *  SRC: HDOJ ACM Steps
 * PROB: IBM Minus One
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        int tasks = cin.nextInt();
        for (int i = 1; i <= tasks; i++) {
            System.out.println("String #" + i);
            char[] str = cin.next().toCharArray();
            for (char c:str)
                System.out.print((char)((c -'A' + 1) % 26 + 'A'));
            System.out.println();
            System.out.println();
        }
    }
}
