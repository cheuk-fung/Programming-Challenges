/*
 *  SRC: POJ 1850
 * PROB: Code
 * ALGO: DP
 * DATE: Mar 29, 2012
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
        int[][] f = new int[11][256];
        int[][] g = new int[11][256];

        for (int curr = 'a'; curr <= 'z'; curr++) {
            f[1][curr] = 1;
            g[1][curr] = g[1][curr - 1] + f[1][curr];
        }

        for (int len = 2; len <= 10; len++) {
            g[len]['a' - 1] = g[len - 1]['z'];
            for (int curr = 'a'; curr <= 'z'; curr++) {
                for (int next = curr + 1; next <= 'z'; next++) {
                    f[len][curr] += f[len - 1][next];
                }
                g[len][curr] = g[len][curr - 1] + f[len][curr];
            }
        }

        String s = cin.next();

        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) <= s.charAt(i - 1)) {
                System.out.println(0);
                return ;
            }
        }

        int res = 1 + g[s.length()][s.charAt(0) - 1];
        for (int i = 1; i < s.length(); i++) {
            res += g[s.length() - i][s.charAt(i) - 1] - g[s.length() - i][s.charAt(i - 1)];
        }

        System.out.println(res);
    }
}
