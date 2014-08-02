/*
 *  SRC: HDOJ 3723
 * PROB: Delta Wave
 * ALGO: Math
 * DATE: Oct 15, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

class Main {
    private static final int MAXN  = 10001;
    private static BigInteger[] fc = new BigInteger[MAXN];

    public static void main(String[] args)
    {
        BigInteger MOD = BigInteger.ONE;
        for (int i = 0; i < 100; i++)
            MOD = MOD.multiply(BigInteger.TEN);

        Scanner cin = new Scanner(System.in);
        BigInteger ans;
        while (cin.hasNext()) {
            int i = cin.nextInt();
            ans = BigInteger.ONE;
            fc[0] = BigInteger.ONE;
            for (int j = 1; 2 * j <= i; j++) {
                fc[j] = fc[j - 1].multiply(BigInteger.valueOf((i - 2 * j + 1) * (i - 2 * j + 2))).divide(BigInteger.valueOf(j * (j + 1)));
                ans = ans.add(fc[j]);
            }
            ans = ans.mod(MOD);
            System.out.println(ans);
        }
    }
}
