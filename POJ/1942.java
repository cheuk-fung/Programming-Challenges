/*
 *  SRC: POJ 1942
 * PROB: Paths on a Grid
 * ALGO: Math
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

    long C(long n, long m)
    {
        long res = 1;
        for (long i = m + 1, j = 1; i <= n; i++) {
            res *= i;
            while (res % j == 0 && j <= n - m) {
                res /= j++;
            }
        }

        return res;
    }

    void solve()
    {
        while (true) {
            long n = cin.nextLong();
            long m = cin.nextLong();
            if ((n | m) == 0) break;

            System.out.println(C(n + m, Math.max(n, m)));
        }
    }
}
