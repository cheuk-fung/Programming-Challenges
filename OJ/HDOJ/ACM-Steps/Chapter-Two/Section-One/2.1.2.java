/*
 *  SRC: HDOJ ACM Steps
 * PROB: How many prime numbers
 * ALGO: check prime
 * DATE: Oct 30, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;

class Main {
    private static boolean check(int p)
    {
        for (int i = 2; i < Math.sqrt(p) + 1; i++)
            if (p % i == 0) return false;
        return true;
    }

    public static void main(String args[])
    {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            int n = cin.nextInt(),
                cnt = 0;
            while (n-- > 0)
                if (check(cin.nextInt())) cnt++;
            System.out.println(cnt);
        }
    }
}
