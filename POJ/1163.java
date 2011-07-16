/*
 *  SRC: POJ 1163
 * PROB: The Triangle
 * ALGO: DP
 * DATE: Jul 16, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    private static int max(int a, int b)
    {
        return a > b ? a : b;
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        int n = cin.nextInt();
        int a[][] = new int[n][n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < i + 1; j++)
                a[i][j] = cin.nextInt();

        for (int i = n - 2; i >= 0; i--)
            for (int j = 0; j < i + 1; j++)
                a[i][j] += max(a[i + 1][j], a[i + 1][j + 1]);

        System.out.println(a[0][0]);
    }
}
