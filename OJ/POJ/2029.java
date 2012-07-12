/*
 *  SRC: POJ 2029
 * PROB: Get Many Persimmon Trees
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

    void solve()
    {
        while (true) {
            int n = cin.nextInt();
            if (n == 0) break;
            int w = cin.nextInt();
            int h = cin.nextInt();
            int[][] mat = new int[w][h];
            for (int i = 0; i < n; i++) {
                int x = cin.nextInt() - 1;
                int y = cin.nextInt() - 1;
                mat[x][y] = 1;
            }

            int[][] row = new int[w][h];
            for (int i = 0; i < w; i++) {
                row[i][0] = mat[i][0];
                for (int j = 1; j < h; j++) {
                    row[i][j] = row[i][j - 1] + mat[i][j];
                }
            }

            int[][] sum = new int[w][h];
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    if (i == 0) sum[i][j] = row[i][j];
                    else sum[i][j] = sum[i - 1][j] + row[i][j];
                }
            }

            int s = cin.nextInt();
            int t = cin.nextInt();
            int ans = 0;
            for (int i = 0; i + s <= w; i++) {
                for (int j = 0; j + t <= h; j++) {
                    int k = i + s - 1;
                    int l = j + t - 1;
                    int cnt = sum[k][l];
                    if (i > 0) cnt -= sum[i - 1][l];
                    if (j > 0) cnt -= sum[k][j - 1];
                    if (i > 0 && j > 0) cnt += sum[i - 1][j - 1];
                    ans = Math.max(ans, cnt);
                }
            }

            System.out.println(ans);
        }
    }
}
