/*
 *  SRC: POJ 1191
 * PROB: 棋盘分割
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
    final static double eps = 1e-8;
    Scanner cin = new Scanner(System.in);

    double avg;
    int[][] mat;
    int[][] sum;
    double[][][][][] f;

    boolean gr(double x, double y) { return x - eps > y; }
    double fmin(double x, double y) { return gr(x, y) ? y : x; }
    double sqr(double x) { return x * x; }

    int getSum(int x1, int y1, int x2, int y2)
    {
        int res = sum[x2][y2];
        if (x1 > 0) res -= sum[x1 - 1][y2];
        if (y1 > 0) res -= sum[x2][y1 - 1];
        if (x1 > 0 && y1 > 0) res += sum[x1 - 1][y1 - 1];
        return res;
    }

    double dp(int n, int x1, int y1, int x2, int y2)
    {
        if (gr(f[n][x1][y1][x2][y2], 0)) return f[n][x1][y1][x2][y2];
        if (n == 0) {
            return f[n][x1][y1][x2][y2] = sqr(getSum(x1, y1, x2, y2) - avg);
        }

        double res = 1e10;
        for (int i = x1; i < x2; i++) {
            double r1 = sqr(getSum(x1, y1, i, y2) - avg) + dp(n - 1, i + 1, y1, x2, y2);
            double r2 = dp(n - 1, x1, y1, i, y2) + sqr(getSum(i + 1, y1, x2, y2) - avg);
            res = fmin(res, fmin(r1, r2));
        }
        for (int i = y1; i < y2; i++) {
            double r1 = sqr(getSum(x1, y1, x2, i) - avg) + dp(n - 1, x1, i + 1, x2, y2);
            double r2 = dp(n - 1, x1, y1, x2, i) + sqr(getSum(x1, i + 1, x2, y2) - avg);
            res = fmin(res, fmin(r1, r2));
        }

        return f[n][x1][y1][x2][y2] = res;
    }

    void solve()
    {
        int n = cin.nextInt();

        mat = new int[8][8];
        avg = 0;
        int[][] row = new int[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                mat[i][j] = cin.nextInt();
                avg += mat[i][j];
                if (j > 0) row[i][j] = row[i][j - 1] + mat[i][j];
                else row[i][j] = mat[i][j];
            }
        }
        avg /= n;

        sum = new int[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (i > 0) sum[i][j] = sum[i - 1][j] + row[i][j];
                else sum[i][j] = row[i][j];
            }
        }

        f = new double[n][8][8][8][8];
        for (int m = 0; m < n; m++)
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    for (int k = 0; k < 8; k++)
                        for (int l = 0; l < 8; l++)
                            f[m][i][j][k][l] = -1.0;
        System.out.printf("%.3f\n", Math.round(Math.sqrt(dp(n - 1, 0, 0, 7, 7) / n) * 1000) / 1000.0);
    }
}
