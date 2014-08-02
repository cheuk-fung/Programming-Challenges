/*
 *  SRC: HDOJ 2446
 * PROB: Shell Pyramid
 * ALGO: Math
 * DATE: Feb 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

class Main {
    public static void main(String args[])
    {
        new Prob().solve();
    }
}

class Prob {
    BigInteger calc(BigInteger x)
    {
        return x.multiply(x.add(BigInteger.ONE)).multiply(x.add(BigInteger.valueOf(2))).divide(BigInteger.valueOf(6));
    }

    BigInteger calc2(BigInteger x)
    {
        return x.multiply(x.add(BigInteger.ONE)).divide(BigInteger.valueOf(2));
    }

    void solve()
    {
        Scanner cin = new Scanner(System.in);
        int n = cin.nextInt();
        while (n-- > 0) {
            BigInteger s = cin.nextBigInteger();
            BigInteger l = BigInteger.ONE, r = BigInteger.valueOf(4000000);
            while (l.compareTo(r) < 0) {
                BigInteger mid = l.add(r).subtract(BigInteger.ONE).divide(BigInteger.valueOf(2));
                if (calc(mid).compareTo(s) >= 0) r = mid;
                else l = mid.add(BigInteger.ONE);
            }
            System.out.print(l + " ");
            BigInteger rest = s.subtract(calc(l.subtract(BigInteger.ONE)));
            l = BigInteger.ONE;
            r = BigInteger.valueOf(2000000);
            while (l.compareTo(r) < 0) {
                BigInteger mid = l.add(r).subtract(BigInteger.ONE).divide(BigInteger.valueOf(2));
                if (calc2(mid).compareTo(rest) >= 0) r = mid;
                else l = mid.add(BigInteger.ONE);
            }
            System.out.print(l + " ");
            System.out.println(rest.subtract(calc2(l.subtract(BigInteger.ONE))));
        }
    }
}
