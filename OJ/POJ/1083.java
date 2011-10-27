/*
 *  SRC: POJ 1083
 * PROB: Moving Tables
 * ALGO: NULL
 * DATE: Jun 4, 2011
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;

class Main
{
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob
{
    private static Scanner cin;

    public void work()
    {
        int[] corr = new int[200];

        int n = cin.nextInt();

        for (int i = 0; i < n; i++) {
            int s = cin.nextInt(), t = cin.nextInt();
            int a = s, b = t;
            if (s > t) {
                a = t;
                b = s;
            }
            if (a % 2 != b % 2) {
                if (b % 2 == 0) b--;
                else b++;
            }
            for (int j = a; j <= b; j += 2) {
                corr[(j - 1) >> 1]++;
            }
        }

        int max = 0;
        for (int i = 0; i < 200; i++)
            max = max > corr[i] ? max : corr[i];

        System.out.println(max * 10);
    }

    public void solve()
    {
        cin = new Scanner(System.in);

        int t = cin.nextInt();

        while (t-- > 0) new Prob().work();
    }
}
