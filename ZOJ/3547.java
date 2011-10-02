/*
 *  SRC: ZOJ 3547
 * PROB: The Boss on Mars
 * ALGO: Number Theory
 * DATE: Oct 02, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

class Main {
    private static final int maxN = 10010;
    private static final BigInteger MOD = BigInteger.valueOf(1000000007);

    private static int n;
    private static int[] p = new int[maxN];
    private static boolean[] b = new boolean[maxN];
    private static int[] fac = new int[10];
    private static int facCnt;
    private static BigInteger ans;

    private static int getPrime(int n)
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

    private static BigInteger calc(BigInteger n, BigInteger coef)
    {
        coef = coef.multiply(coef);
        coef = coef.multiply(coef);
        BigInteger a = n.add(BigInteger.ONE), // n + 1
                   b = n.multiply(BigInteger.valueOf(2)).add(BigInteger.ONE), // 2 * n + 1
                   c = n.multiply(n).multiply(BigInteger.valueOf(3)).add(n.multiply(BigInteger.valueOf(3))).subtract(BigInteger.ONE); // 3 * n * n + 3 * n - 1
        return coef.multiply(n.multiply(a).multiply(b).multiply(c).divide(BigInteger.valueOf(30)));
    }

    private static void dfs(int prev, int step, int tot)
    {
        for (int i = prev + 1; i < facCnt; i++) {
            int tmp = tot * fac[i];
            if (step % 2 == 1) ans = ans.subtract(calc(BigInteger.valueOf(n / tmp), BigInteger.valueOf(tmp)));
            else ans = ans.add(calc(BigInteger.valueOf(n / tmp), BigInteger.valueOf(tmp)));
            dfs(i, step + 1, tmp);
        }
    }

    public static void main(String[] args) {
        int prmCnt = getPrime(maxN);

        Scanner cin = new Scanner(System.in);

        int T = cin.nextInt();
        while (T-- != 0) {
            n = cin.nextInt();

            facCnt = 0;
            int tmp = n;
            for (int i = 0; p[i] <= Math.sqrt(n); i++) {
                if (tmp % p[i] == 0) {
                    fac[facCnt++] = p[i];
                    while (tmp % p[i] == 0) tmp /= p[i];
                }
                if (tmp == 1) break;
            }
            if (tmp != 1) fac[facCnt++] = tmp;

            ans = calc(BigInteger.valueOf(n), BigInteger.ONE);
            dfs(-1, 1, 1);
            System.out.println(ans.mod(MOD));
        }
    }
}
