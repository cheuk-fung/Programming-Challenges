/*
 *  SRC: POJ 3176
 * PROB: Cow Bowling
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

    void solve()
    {
        int n = cin.nextInt();
        int[][] triangle = new int[n][];
        for (int i = 0; i < n; i++) {
            triangle[i] = new int[i + 1];
            for (int j = 0; j <= i; j++)
                triangle[i][j] = cin.nextInt();
        }

        int[][] f = new int[n][];
        f[n - 1] = new int[n];
        for (int j = 0; j < n; j++) {
            f[n - 1][j] = triangle[n - 1][j];
        }
        for (int i = n - 2; i >= 0; i--) {
            f[i] = new int[i + 1];
            for (int j = 0; j <= i; j++) {
                f[i][j] = Math.max(f[i + 1][j], f[i + 1][j + 1]) + triangle[i][j];
            }
        }

        System.out.println(f[0][0]);
    }
}
