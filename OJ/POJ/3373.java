/*
 *  SRC: POJ 3373
 * PROB: Changing Digits
 * ALGO: Memorize Search
 * DATE: Jul 11, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static Scanner cin = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(System.out);

    int k, best;
    char[] n;
    char[] m;
    boolean[][][] f;

    void search(int now, int cnt, int mod)
    {
        if (cnt >= best) return ;

        if (now == n.length) {
            if (mod == 0) {
                best = cnt;
                m = (char[])n.clone();
            }
            return ;
        }

        if (f[cnt][now][mod]) return ;
        f[cnt][now][mod] = true;

        char orig = n[now];
        char start = now == 0 ? '1' : '0';
        for (char c = start; c <= '9'; c++) {
            n[now] = c;
            search(now + 1, cnt + (c == orig ? 0 : 1), (mod * 10 + (c - '0')) % k);
        }
        n[now] = orig;
    }

    void solve()
    {
        while (cin.hasNext()) {
            n = cin.next().toCharArray();
            k = cin.nextInt();

            best = (int)(Math.log10(k + 1) + 1) + 2;
            f = new boolean[best][n.length][k];

            search(0, 0, 0);
            out.println(m);
        }
        out.flush();
    }
}
