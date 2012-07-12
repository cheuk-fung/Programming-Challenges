/*
 *  SRC: POJ 1925
 * PROB: Spiderman
 * ALGO: DP
 * DATE: Jul 12, 2012
 * COMP: g++
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
    Scanner cin = new Scanner(System.in);
    final static int INF = 0x3f3f3f3f;

    long sqr(long x) { return x * x; }

    void solve()
    {
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int n = cin.nextInt();
            int[] x = new int[n];
            int[] y = new int[n];
            long[] diffy = new long[n];
            for (int i = 0; i < n; i++) {
                x[i] = cin.nextInt();
                y[i] = cin.nextInt();
                diffy[i] = sqr(y[i]) - sqr(y[i] - y[0]);
            }

            int m = x[n - 1];
            int ans = INF;
            int[] f = new int[m];
            Arrays.fill(f, INF);
            f[x[0]] = 0;
            for (int i = 1; i < n; i++) {
                for (int j = x[i] - 1; j >= x[0]; j--) {
                    if (sqr(x[i] - j) > diffy[i]) break;
                    if (f[j] == INF) continue;

                    int to = 2 * x[i] - j;
                    if (to >= m) {
                        ans = Math.min(ans, f[j] + 1);
                    } else {
                        f[to] = Math.min(f[to], f[j] + 1);
                    }
                }
            }

            System.out.println(ans == INF ? -1 : ans);
        }
    }
}
