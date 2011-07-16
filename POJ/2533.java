/*
 *  SRC: POJ 2533
 * PROB: Longest Ordered Subsequence
 * ALGO: DP
 * DATE: Jul 16, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        int n = cin.nextInt();
        int a[] = new int[n];
        for (int i = 0; i < n; i++)
            a[i] = cin.nextInt();

        int f[] = new int[n], ans = 0;
        for (int i = 0; i < n; i++) f[i] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (a[i] > a[j] && f[i] <= f[j])
                    f[i] = f[j] + 1;
            }
            if (ans < f[i]) ans = f[i];
        }

        System.out.println(ans);
    }
}
