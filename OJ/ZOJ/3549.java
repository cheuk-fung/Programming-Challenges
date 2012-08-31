/*
 *  SRC: ZOJ 3549
 * PROB: Little Keng
 * ALGO: Bisection
 * DATE: Aug 31, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ng
 */

import java.util.*;
import java.math.BigInteger;

class Main {
    boolean check(int mid, int m, int n)
    {
        String modstr = "1";
        for (int i = 0; i < mid; i++) modstr += "0";
        BigInteger MOD = new BigInteger(modstr);

        BigInteger res = BigInteger.ZERO;
        for (int i = 1; i <= m; i++) {
            BigInteger now = BigInteger.ONE;
            BigInteger a = BigInteger.valueOf(i);
            int b = n;
            while (b != 0) {
                if ((b & 1) != 0) now = now.multiply(a).mod(MOD);
                a = a.multiply(a).mod(MOD);
                b >>= 1;
            }
            res = res.add(now).mod(MOD);
        }
        return res.mod(MOD).equals(BigInteger.ZERO);
    }

    void run()
    {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            int m = cin.nextInt();
            int n = cin.nextInt();

            int l = 0, r = 20;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (check(mid, m, n)) l = mid;
                else r = mid - 1;
            }
            System.out.println(l);
        }
    }

    public static void main(String[] args)
    {
        new Main().run();
    }
}
