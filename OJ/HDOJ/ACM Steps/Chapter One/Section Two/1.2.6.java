/*
 *  SRC: HDOJ ACM Steps
 * PROB: Specialized Four-Digit Numbers
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    private static boolean check(int p)
    {
        int a = p / 1000 + (p % 1000 / 100) + (p % 100 / 10) + p % 10,
            b = p / 4096 + (p % 4096 / 256) + (p % 256 / 16) + p % 16,
            c = p / 1728 + (p % 1728 / 144) + (p % 144 / 12) + p % 12;
        return a == b && b == c;
    }

    public static void main(String[] args)
    {
        for (int i = 1000; i < 10000; i++)
            if (check(i)) System.out.println(i);
    }
}
