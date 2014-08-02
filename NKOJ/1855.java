/*
 *  SRC: NKOJ 1855
 * PROB: And Then There Was One
 * ALGO: NULL
 * DATE: Mar 03, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    int josephus(int n, int m)
    {
        int x = 1;
        for (int i = 2; i <= n; i++) x = (x + m - 1) % i + 1;
        return x;
    }

    void solve()
    {
        while (cin.hasNext()) {
            int n = cin.nextInt();
            int k = cin.nextInt();
            int m = cin.nextInt();
            if (n == 0 && k == 0 && m == 0) break;

            int ans = (josephus(n, k) - k % n + n + m) % n;
            if (ans == 0) ans = n;
            System.out.println(ans);
        }
    }
}