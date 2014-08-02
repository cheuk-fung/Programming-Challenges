/*
 *  SRC: POJ 4006
 * PROB: Genghis Khan the Conqueror
 * ALGO: Tree DP + MST
 * DATE: Sep 27, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

class Main {
    private ArrayList<ArrayList<Integer>> edge;
    private int[][] f;

    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        MyReader in = new MyReader();

        while (true) {
            int n = in.nextInt();
            int m = in.nextInt();
            if (n == 0 && m == 0) break;

            int[][] mat = new int[n][n];
            for (int i = 0; i < n; i++) Arrays.fill(mat[i], Integer.MAX_VALUE);
            for (int i = 0; i < m; i++) {
                int x = in.nextInt();
                int y = in.nextInt();
                int c = in.nextInt();
                mat[x][y] = mat[y][x] = c;
            }
            f = new int[n][n];
            for (int i = 0; i < n; i++) f[i] = mat[i].clone();

            edge = new ArrayList<ArrayList<Integer>>();
            for (int i = 0; i < n; i++) edge.add(new ArrayList<Integer>());
            int[] dist = new int[n];
            int[] father = new int[n];
            Arrays.fill(dist, Integer.MAX_VALUE);
            long mst = 0;
            for (int i = 1, u = 0; i < n; i++) {
                dist[u] = -1;
                for (int j = 0; j < n; j++) {
                    if (mat[u][j] < dist[j]) {
                        dist[j] = mat[u][j];
                        father[j] = u;
                    }
                }

                u = -1;
                for (int j = 0; j < n; j++) {
                    if (dist[j] != -1 && (u == -1 || dist[j] < dist[u])) {
                        u = j;
                    }
                }
                mst += dist[u];

                edge.get(father[u]).add(u);
                edge.get(u).add(father[u]);
                f[father[u]][u] = f[u][father[u]] = Integer.MAX_VALUE;
            }

            for (int i = 0; i < n; i++) {
                dfs0(i, -1, i);
            }

            int[][] g = new int[n][n];
            for (int i = 0; i < n; i++) Arrays.fill(g[i], -1);
            for (int i = 1; i < n; i++) {
                int j = father[i];
                g[i][j] = g[j][i] = dfs1(i, j, j);
            }


            int q = in.nextInt();
            double total = mst * q;
            for (int i = 0; i < q; i++) {
                int x = in.nextInt();
                int y = in.nextInt();
                int c = in.nextInt();
                if (g[x][y] != -1) total += Math.min(g[x][y], c) - mat[x][y];
            }

            System.out.printf("%.4f%n", total / q);
        }
    }

    private int dfs0(int u, int father, int x)
    {
        for (int v : edge.get(u)) {
            if (v != father) {
                f[x][u] = Math.min(f[x][u], dfs0(v, u, x));
            }
        }
        return f[x][u];
    }

    private int dfs1(int u, int father, int x)
    {
        int r = f[u][x];
        for (int v : edge.get(u)) {
            if (v != father) {
                r = Math.min(r, dfs1(v, u, x));
            }
        }
        return r;
    }

    class MyReader {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer token;

        boolean hasNext()
        {
            while (token == null || !token.hasMoreTokens()) {
                try {
                    token = new StringTokenizer(br.readLine());
                } catch (Exception e) {
                    return false;
                }
            }
            return true;
        }

        String next()
        {
            if (hasNext()) return token.nextToken();
            return null;
        }

        int nextInt() { return Integer.parseInt(next()); }
    }
}
