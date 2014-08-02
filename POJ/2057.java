/*
 *  SRC: POJ 2057
 * PROB: The Lost House
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

    ArrayList<ArrayList<Integer>> edge;
    boolean[] hasWorm;
    int[] f;
    int[] g;
    int[] l;

    class NodeComparator implements Comparator<Integer> {
        public int compare(Integer u, Integer v)
        {
            return (g[u] + 2) * l[v] - (g[v] + 2) * l[u];
        }
    }

    int dp(int u)
    {
        if (edge.get(u).isEmpty()) {
            return l[u] = 1;
        }

        for (int v : edge.get(u)) {
            l[u] += dp(v);
            if (!hasWorm[u]) {
                g[u] += g[v] + 2;
            }
        }

        Collections.sort(edge.get(u), new NodeComparator());
        int coef = 1;
        for (int v : edge.get(u)) {
            f[u] += coef * l[v] + f[v];
            coef += g[v] + 2;
        }

        return l[u];
    }

    void solve()
    {
        while (true) {
            int n = cin.nextInt();
            if (n == 0) break;

            hasWorm = new boolean[n];
            edge = new ArrayList<ArrayList<Integer>>(n);
            for (int i = 0; i < n; i++) {
                edge.add(new ArrayList<Integer>());
            }
            for (int v = 0; v < n; v++) {
                int u = cin.nextInt() - 1;
                String s = cin.next();
                if (u >= 0) {
                    edge.get(u).add(v);
                    hasWorm[v] = s.equals("Y");
                }
            }

            f = new int[n];
            g = new int[n];
            l = new int[n];
            dp(0);
            System.out.printf("%.4f\n", (double)f[0] / l[0]);
        }
    }
}
