/*
 *  SRC: POJ 1947
 * PROB: Rebuilding Roads
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
    final int INF = 0x3f3f3f3f;

    ArrayList<ArrayList<Integer>> tree;
    int root, p;
    int ans = INF;
    int[] size;

    int[] dp(int u)
    {
        int[] res = new int[p + 1];
        Arrays.fill(res, INF);

        size[u] = 1;
        res[0] = 1;
        res[1] = tree.get(u).size();
        for (int i = 0; i < tree.get(u).size(); i++) {
            int v = tree.get(u).get(i);
            int[] child = dp(v);
            size[u] += size[v];

            for (int val = p; val > 1; val--) {
                for (int dv = Math.min(p, size[v]); dv >= 0; dv--) {
                    if (val - dv > 0) {
                        res[val] = Math.min(res[val], res[val - dv] - 1 + child[dv]);
                    }
                }
            }
        }

        ans = Math.min(ans, res[p] + (u == root ? 0 : 1));

        return res;
    }

    void solve()
    {
        int n = cin.nextInt();
        p = cin.nextInt();

        tree = new ArrayList<ArrayList<Integer>>(n);
        for (int i = 0; i < n; i++) tree.add(new ArrayList<Integer>());

        int[] degree = new int[n];
        for (int i = 1; i < n; i++) {
            int u = cin.nextInt();
            int v = cin.nextInt();
            tree.get(u - 1).add(v - 1);
            degree[v - 1]++;
        }

        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                root = i;
                break;
            }
        }

        size = new int[n];
        dp(root);
        System.out.println(ans);
    }
}
