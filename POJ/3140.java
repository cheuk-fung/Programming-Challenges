/*
 *  SRC: POJ 3140
 * PROB: Contestants Division
 * ALGO: Tree DP
 * DATE: Jul 13, 2012
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
    Scanner cin = new Scanner(System.in);

    ArrayList<ArrayList<Integer>> tree;
    long tot;
    long ans;
    long[] peo;
    long[] size;

    long dp(int u, int parent)
    {
        size[u] = peo[u];
        for (int v : tree.get(u)) {
            if (v != parent) {
                size[u] += dp(v, u);
            }
        }
        ans = Math.min(ans, Math.abs(tot - size[u] * 2));
        return size[u];
    }

    void solve()
    {
        for (int task = 1; ; task++) {
            int n = cin.nextInt();
            int m = cin.nextInt();
            if (n == 0 && m == 0) break;

            tot = 0;
            peo = new long[n];
            for (int i = 0; i < n; i++) {
                peo[i] = cin.nextLong();
                tot += peo[i];
            }

            tree = new ArrayList<ArrayList<Integer>>(n);
            for (int i = 0; i < n; i++) tree.add(new ArrayList<Integer>());
            for (int i = 0; i < m; i++) {
                int u = cin.nextInt() - 1;
                int v = cin.nextInt() - 1;
                tree.get(u).add(v);
                tree.get(v).add(u);
            }

            size = new long[n];
            ans = 0x7fffffffffffffffl;
            dp(0, -1);

            System.out.println("Case " + task + ": " + ans);
        }
    }
}
