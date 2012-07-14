/*
 *  SRC: POJ 1189
 * PROB: 钉子和小球
 * ALGO: DP
 * DATE: Jul 14, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

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
        int n = cin.nextInt();
        int m = cin.nextInt();
        boolean[][] mat = new boolean[n + 1][n + 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                String c = cin.next();
                if (c.equals("*")) mat[i][j] = true;
                else mat[i][j] = false;
            }
        }

        long[][] f = new long[n + 1][n + 1];
        f[0][0] = 1l << n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (mat[i][j]) {
                    f[i + 1][j] += f[i][j] >> 1;
                    f[i + 1][j + 1] += f[i][j] >> 1;
                } else {
                    f[i + 2][j + 1] += f[i][j];
                }
            }
        }

        long g = BigInteger.valueOf(f[n][m]).gcd(BigInteger.valueOf(f[0][0])).longValue();
        System.out.println(f[n][m] / g + "/" + f[0][0] / g);
    }
}
