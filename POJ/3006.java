/*
 *  SRC: POJ 3006
 * PROB: Dirichlet's Theorem on Arithmetic Progressions
 * ALGO: Prime
 * DATE: Jul 12, 2011 
 * COMP: jkd 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    private static final int MAXSUM = (int)1e6;
    private static int[] p = new int[MAXSUM];
    private static boolean[] b = new boolean[MAXSUM];
    private static int pSum;

    public static void getPrime()
    {
        int pSum = 0;
        b[0] = b[1] = false;
        for (int i = 2; i < MAXSUM; i++) b[i] = true;
        for (int i = 2; i < MAXSUM; i++) {
            if (b[i] == true) p[pSum++] = i;
            for (int j = 0; j < pSum && i * p[j] < MAXSUM; j++) {
                b[i * p[j]] = false;
                if (i % p[j] == 0) break;
            }
        }
    }

    public static void main(String[] args)
    {
        getPrime();

        Scanner cin = new Scanner(System.in);

        while (1 + 1 == 2) {
            int a = cin.nextInt(), d = cin.nextInt(), n = cin.nextInt();
            if (a == 0 && d == 0 && n == 0) break;

            int cnt = 0;
            while (cnt < n) {
                if (b[a] == true) cnt++;
                a += d;
            }

            System.out.println(a - d);
        }
    }
}
