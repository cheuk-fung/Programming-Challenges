/*
 *  SRC: POJ 1260
 * PROB: Pearls
 * ALGO: DP
 * DATE: Mar 16, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);
    static final int INF = 0x3f3f3f3f;

    void solve()
    {
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int c = cin.nextInt();
            int[] a = new int[c + 1];
            int[] p = new int[c + 1];
            int[] sum = new int[c + 1];
            int[] f = new int[c + 1];

            for (int i = 1; i <= c; i++) {
                a[i] = cin.nextInt();
                p[i] = cin.nextInt();
                sum[i]  = sum[i - 1] + a[i];
            }

            for (int i = 1; i <= c; i++) {
                f[i] = (sum[i] + 10) * p[i];
                for (int j = 1; j < i; j++) {
                    f[i] = Math.min(f[i], f[j] + (sum[i] - sum[j] + 10) * p[i]);
                }
            }

            System.out.println(f[c]);
        }
    }
}
