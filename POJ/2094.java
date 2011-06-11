/*
 *  SRC: POJ 2094
 * PROB: Angry Teacher
 * ALGO: Math & BigInteger
 * DATE: Jun 1, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;
import java.math.BigInteger;

class Main
{
    private static int n, k, m;
    private static BigInteger l;
    private static BigInteger[] a;
    private static BigInteger[][] table;
    private static BigInteger MOD;

    public static void calc(int p)
    {
        BigInteger mt = BigInteger.ONE;
        table[0][p] = a[n];

        for (int i = n - 1; i >= 0; i--) {
            mt = mt.multiply(l).mod(MOD);
            table[0][p] = table[0][p].add(a[i].multiply(mt).mod(MOD)).mod(MOD);
        }
        l = l.add(BigInteger.ONE);
    }

    public static void getAns(String p)
    {
        int ans = 0;
        for (int i = p.length() - 1, j = 0; i >= 0 && j < m; i--, j++) ans += (p.charAt(i) - '0') * (p.charAt(i) - '0');
        System.out.println(ans);
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        n = cin.nextInt();
        l = new BigInteger(cin.next());
        k = cin.nextInt();
        m = cin.nextInt();
        MOD = BigInteger.TEN.pow(m + 10);

        a = new BigInteger[n + 1];
        for (int i = 0; i <= n; i++)
            a[i] = new BigInteger(cin.next());

        table = new BigInteger[n + 1][];
        int tableSize = n + 1 > k ? n + 1 : k;
        for (int i = 0; i <= n; i++)
            table[i] = new BigInteger[tableSize];

        for (int i = 0; i <= n; i++) calc(i);

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= n - i; j++) {
                table[i][j] = table[i - 1][j + 1].add(MOD).subtract(table[i - 1][j]).mod(MOD);
            }

        if (k <= n + 1) {
            for (int i = 0; i < k; i++) getAns(table[0][i].toString());
            System.exit(0);
        }

        for (int i = 0; i < k; i++) table[n][i] = table[n][0];
        for (int i = n - 1; i >= 0; i--)
            for (int j = n + 1 - i; j < k; j++)
                table[i][j] = table[i + 1][j - 1].add(table[i][j - 1]).mod(MOD);

        for (int i = 0; i < k; i++) getAns(table[0][i].toString());
    }
}

