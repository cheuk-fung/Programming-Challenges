/*
 *  SRC: POJ 3273
 * PROB: Monthly Expense
 * ALGO: Bisection
 * DATE: Jun 6, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    private static int n, m;
    private static int[] cost;

    public static boolean check(long max)
    {
        int sum = 0;
        long tot = 0;
        for (int i = 0; i < n; i++) {
            tot += cost[i];
            if (tot > max) {
                tot = cost[i];
                sum++;
            }
        }
        sum++;

        if (sum > m) return true;
        return false;
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        n = cin.nextInt();
        m = cin.nextInt();

        cost = new int[n];
        long low = 0, high = 0;
        for (int i = 0; i < n; i++) {
            cost[i] = cin.nextInt();
            high += cost[i];
            if (cost[i] > low) low = cost[i];
        }

        while (low < high) {
            long mid = (low + high - 1) / 2;
            if (check(mid) == true) low = mid + 1;
            else high = mid;
        }

        System.out.println(low);
    }
}
