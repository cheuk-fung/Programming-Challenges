/*
 *  SRC: POJ 2478
 * PROB: Farey Sequence
 * ALGO: Number Theory
 * DATE: Sep 06, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;
import static java.lang.Math.sqrt;

class Main {
    static final int MAX_N = 1000001;
    static int[] prm = new int[78500];
    static boolean[] isPrm = new boolean[MAX_N];
    static int prm_cnt;
    static int[] phi = new int[MAX_N];
    static long[] f = new long[MAX_N];

    static int getPrime(int n)
    {
        int cnt = 0;
        isPrm[0] = isPrm[1] = false;
        for (int i = 2; i < n; i++) isPrm[i] = true;
        for (int i = 2; i < n; i++) {
            if (isPrm[i]) prm[cnt++] = i;
            for (int j = 0; j < cnt && i * prm[j] < n; j++) {
                isPrm[i * prm[j]] = false;
                if (i % prm[j] == 0) break;
            }
        }
        return cnt;

    }

    static void euler(int n)
    {
        phi[1] = 1;
        for (int i = 2; i < n; i++) {
            if (isPrm[i]) phi[i] = i - 1;
            else {
                for (int j = 0; j < prm_cnt; j++)
                    if (i % prm[j] == 0) {
                        int k = i / prm[j];
                        if (k % prm[j] == 0) phi[i] = phi[k] * prm[j];
                        else phi[i] = phi[k] * (prm[j] - 1);
                        break;
                    }
            }
        }
    }

    public static void main(String[] argv)
    {
        prm_cnt = getPrime(MAX_N);
        euler(MAX_N);
        for (int i = 2; i < MAX_N; i++)
            f[i] = f[i - 1] + phi[i];

        Scanner cin = new Scanner(System.in);
        int x;
        while ((x = cin.nextInt()) != 0) System.out.println(f[x]);
    }
}
