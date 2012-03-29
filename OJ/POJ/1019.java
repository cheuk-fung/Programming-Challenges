/*
 *  SRC: POJ 1019
 * PROB: Number Sequence
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
        Vector<Long> f = new Vector<Long>();
        Vector<Long> g = new Vector<Long>();
        f.add(0L);
        g.add(0L);
        for (int i = 1; g.lastElement() < 2147483647; i++) {
            f.add(f.lastElement() + (long)(Math.ceil(Math.log10(i + 1))));
            g.add(g.lastElement() + f.lastElement());
        }

        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int n = cin.nextInt();
            int l = 0, r = g.size() - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (g.get(mid) <= n) l = mid;
                else r = mid - 1;
            }

            n -= g.get(l);
            if (n == 0) {
                System.out.println(l % 10);
            } else {
                for (int i = 1; i <= l + 1; i++) {
                    int len = (int)(Math.ceil(Math.log10(i + 1)));
                    if (n <= len) {
                        System.out.println(i / (int)Math.pow(10, len - n) % 10);
                        break;
                    } else {
                        n -= len;
                    }
                }
            }
        }
    }
}
