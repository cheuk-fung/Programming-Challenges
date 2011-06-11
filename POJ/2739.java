/*
 *  SRC: POJ 2739
 * PROB: Sum of Consecutive Prime Numbers
 * ALGO: Prime
 * DATE: Jun 5, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;

class Main
{
    private static final int MAX = 10010;
    private static int[] p = new int[MAX];

    public static int getPrime()
    {
        boolean[] b = new boolean[MAX];

        int pSum = 0;
        for (int i = 0; i < MAX; i++) b[i] = true;
        for (int i = 2; i < MAX; i++) {
            if (b[i] == true) p[pSum++] = i;
            for (int j = 0; j < pSum && i * p[j] < MAX; j++) {
                b[i * p[j]] = false;
                if (i % p[j] == 0) break;
            }
        }

        return pSum;
    }

    public static void main(String[] args)
    {
        int pSum = getPrime();

        int[] f = new int[MAX];
        for (int l = 1; l <= pSum; l++)
            for (int i = 0; i + l <= pSum; i++) {
                int tot = 0;
                for (int j = 0; j < l; j++) tot += p[i + j];
                if (tot <= MAX) f[tot]++;
            }

        Scanner cin = new Scanner(System.in);

        while (1 + 1 == 2) {
            int t = cin.nextInt();
            if (t == 0) break;
            System.out.println(f[t]);
        }
    }
}

