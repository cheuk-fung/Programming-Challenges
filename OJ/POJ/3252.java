/*
 *  SRC: POJ 3252
 * PROB: Round Numbers
 * ALGO: DP
 * DATE: Mar 25, 2012
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

    int[][] f = new int[33][33];
    int[][] g = new int[33][33];

    int calc(int x)
    {
        int bitCnt = 0;
        for ( ; x >> bitCnt > 0; bitCnt++)
            ;

        int res = 0;
        for (int i = 1; i < bitCnt; i++) {
            res += g[i - 1][(i + 1) / 2];
        }

        int zeroCnt = 0;
        for (int i = bitCnt - 2; i >= 0; i--) {
            if ((x >> i & 1) == 0) {
                zeroCnt++;
            } else {
                int cnt = (bitCnt + 1) / 2 - zeroCnt - 1;
                if (cnt < 0) cnt = 0;
                res += g[i][cnt];
            }
        }

        return res;
    }

    void solve()
    {
        f[0][0] = 1;
        for (int i = 1; i < 32; i++) {
            f[i][0] = f[i - 1][0];
            for (int j = 1; j <= i; j++) {
                f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
            }
        }

        g[0][0] = 1;
        for (int i = 1; i < 32; i++) {
            for (int j = i; j >= 0; j--) {
                g[i][j] = g[i][j + 1] + f[i][j];
            }
        }

        int start = cin.nextInt();
        int finish = cin.nextInt();

        System.out.println(calc(finish + 1) - calc(start));
    }

    static void debug(Object...o)
    {
        System.err.println(Arrays.deepToString(o));
    }
}
