/*
 *  SRC: HDOJ 4002
 * PROB: Find the maximum
 * ALGO: Number Theory
 * DATE: Sep 03, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

class Main {
    static final int MAX_PRM = 1000;
    static int[] p = new int[MAX_PRM];
    static boolean[] b = new boolean[MAX_PRM];

    static int getPrime(int n)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++) b[i] = true;
        b[0] = b[1] = false;
        for (int i = 2; i < n; i++) {
            if (b[i]) p[cnt++] = i;
            for (int j = 0; j < cnt && i * p[j] < n; j++) {
                b[i * p[j]] = false;
                if (i % p[j] == 0) break;
            }
        }

        return cnt;
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        int prmCnt = getPrime(MAX_PRM),
            jobs = cin.nextInt();

        while (jobs-- > 0) {
            BigInteger n = cin.nextBigInteger(),
                       ans = BigInteger.ONE,
                       t;

            for (int i = 0; i < prmCnt; i++) {
                t = ans.multiply(BigInteger.valueOf(p[i]));
                if (t.compareTo(n) > 0) {
                    System.out.println(ans);
                    break;
                }
                ans = t;
            }
        }
    }
}
