/*
 *  SRC: POJ 3267
 * PROB: The Cow Lexicon
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
        int w = cin.nextInt();
        int l = cin.nextInt();
        String s = cin.next();
        String[] words = new String[w];
        for (int i = 0; i < w; i++) {
            words[i] = cin.next();
        }

        int[] f = new int[l + 1];
        int[] g = new int[w];
        f[0] = 0;
        for (int i = 1; i <= l; i++) {
            f[i] = 0x3f3f3f3f;

            for (int k = 0; k < w; k++) {
                g[k] = words[k].length() - 1;
            }

            for (int j = i; j > 0; j--) {
                for (int k = 0; k < w; k++) {
                    if (g[k] >= 0 && s.charAt(j - 1) == words[k].charAt(g[k])) {
                        g[k]--;
                    }
                    if (g[k] < 0) {
                        f[i] = Math.min(f[i], f[j - 1] + i - j + 1 - words[k].length());
                    }
                }
            }
        }

        System.out.println(f[l]);
    }
}
