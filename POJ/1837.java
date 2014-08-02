/*
 *  SRC: POJ 1837
 * PROB: Balance
 * ALGO: DP
 * DATE: Mar 08, 2012
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
        int c = cin.nextInt();
        int g = cin.nextInt();
        int[] hooks = new int[c];
        int[] weights = new int[g];

        for (int i = 0; i < c; i++)
            hooks[i] = cin.nextInt();
        for (int i = 0; i < g; i++)
            weights[i] = cin.nextInt();

        int offset = 10000;
        int[][] a = new int[g][c];
        for (int i = 0; i < g; i++)
            for (int j = 0; j < c; j++)
                a[i][j] = weights[i] * hooks[j] + offset;

        int[][] f = new int[g + 1][offset * g + 1];
        f[0][0] = 1;
        for (int i = 1; i <= g; i++) {
            for (int j = 0; j < c; j++) {
                for (int v = offset * g; v >= a[i - 1][j]; v--)
                    f[i][v] += f[i - 1][v - a[i - 1][j]];
            }
        }

        System.out.println(f[g][offset * g]);
    }
}
