/*
 *  SRC: POJ 1276
 * PROB: Cash Machine
 * ALGO: DP
 * DATE: Mar 14, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    void zeroOnePack(boolean[] f, int value, int maxValue)
    {
        for (int i = maxValue; i >= value; i--)
            if (f[i - value] == true) f[i] = true;
    }

    void completePack(boolean[] f, int value, int maxValue)
    {
        for (int i = value; i <= maxValue; i++)
            if (f[i - value] == true) f[i] = true;
    }

    void multiplePack(boolean[] f, int amount, int value, int maxValue)
    {
        if (value * amount >= maxValue)
            completePack(f, value, maxValue);
        else {
            for (int k = 1; k < amount; amount -= k, k <<= 1)
                zeroOnePack(f, k * value, maxValue);

            zeroOnePack(f, value * amount, maxValue);
        }
    }

    void solve()
    {
        while (cin.hasNext()) {
            int cash = cin.nextInt();
            int n = cin.nextInt();
            boolean[] f = new boolean[cash + 1];

            f[0] = true;
            for (int i = 0; i < n; i++) {
                multiplePack(f, cin.nextInt(), cin.nextInt(), cash);
            }

            for (int i = cash; i >= 0; i--) {
                if (f[i]) {
                    System.out.println(i);
                    break;
                }
            }
        }
    }
}
