/*
 *  SRC: POJ 2948
 * PROB: Martian Mining
 * ALGO: DP
 * DATE: Jul 12, 2012
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

    int[][] f;
    int[][] yeyenum;
    int[][] bloggium;

    int dp(int x, int y)
    {
        if (x < 0 || y < 0) return 0;
        if (f[x][y] != -1) return f[x][y];

        int res = dp(x - 1, y - 1) + Math.max(yeyenum[x][y], bloggium[x][y]);
        res = Math.max(res, dp(x, y - 1) + bloggium[x][y]);
        res = Math.max(res, dp(x - 1, y) + yeyenum[x][y]);

        return f[x][y] = res;
    }

    void solve()
    {
        while (true) {
            int n = cin.nextInt();
            int m = cin.nextInt();
            if (n == 0 && m == 0) break;

            yeyenum = new int[n][m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    yeyenum[i][j] = cin.nextInt();
                    if (j > 0) yeyenum[i][j] += yeyenum[i][j - 1];
                }
            }

            bloggium = new int[n][m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    bloggium[i][j] = cin.nextInt();
                    if (i > 0) bloggium[i][j] += bloggium[i - 1][j];
                }
            }

            f = new int[n][m];
            for (int i = 0; i < n; i++) Arrays.fill(f[i], -1);
            System.out.println(dp(n - 1, m - 1));
        }
    }
}
