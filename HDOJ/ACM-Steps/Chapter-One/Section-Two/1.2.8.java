/*
 *  SRC: HDOJ ACM Steps
 * PROB: Vowel Counting
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;
import static java.lang.Character.*;

class Main {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            char[] str = cin.next().toCharArray();
            for (char c:str) {
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
                    System.out.print(toUpperCase(c));
                else System.out.print(toLowerCase(c));
            }
            System.out.println();
        }
    }
}
