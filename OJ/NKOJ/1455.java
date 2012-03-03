/*
 *  SRC: NKOJ 1455
 * PROB: Bridging signals
 * ALGO: DP
 * DATE: Mar 03, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);
    static final int INF = 0x3f3f3f3f;

    int lowerBound(int[] a, int v)
    {
        int l = 0, r = a.length - 1;
        while (l < r) {
            int mid = (l + r - 1) / 2;
            if (a[mid] < v) l = mid + 1;
            else r = mid;
        }
        return l;
    }

    void solve()
    {
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int p = cin.nextInt();
            int[] g = new int[p];
            for (int i = 0; i < p; i++) g[i] = INF;
            for (int i = 0; i < p; i++) {
                int v = cin.nextInt();
                int j = lowerBound(g, v);
                g[j] = v;
            }
            for (int i = p - 1; i >= 0; i--)
                if (g[i] < INF) {
                    System.out.println(i + 1);
                    break;
                }
        }
    }
}
