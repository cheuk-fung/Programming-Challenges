/*
 *  SRC: POJ 3274
 * PROB: Gold Balanced Lineup
 * ALGO: Bisection
 * DATE: Mar 05, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;
import java.util.Vector;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Cow {
    int[] bitSum;
    int id;

    Cow(int[] _bitSum, int _id)
    {
        bitSum = _bitSum;
        id = _id;
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    int getCode(int[] bit, final int MOD)
    {
        int h = 0;
        for (int key : bit) {
            h = (h << 4) + key;
            int g = h & 0xF0000000;
            if (g != 0) h ^= g >> 24;
            h &= ~g;
        }
        return Math.abs(h) % MOD;
    }

    boolean check(int[] a, int[] b)
    {
        for (int i = 0; i < a.length; i++)
            if (a[i] != b[i]) return false;
        return true;
    }

    void solve()
    {
        int n = cin.nextInt();
        int k = cin.nextInt();
        int[] features = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            features[i] = cin.nextInt();
        }

        int[][] bitSum = new int[n + 1][k];
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < k; j++) {
                if (i > 0) bitSum[i][j] = bitSum[i - 1][j];
                if ((features[i] & (1 << j)) > 0) bitSum[i][j]++;
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < k; j++) {
                bitSum[i][j] -= bitSum[i][0];
            }
            bitSum[i][0] = 0;
        }

        int ans = 0;
        Vector<Cow>[] hashTable = new Vector[n];
        for (int i = 0; i < n; i++) {
            hashTable[i] = new Vector<Cow>();
        }
        for (int i = 0; i <= n; i++) {
            int code = getCode(bitSum[i], n);
            if (hashTable[code].isEmpty()) {
                hashTable[code].add(new Cow(bitSum[i], i));
            }
            else {
                boolean found = false;
                for (Cow tmp : hashTable[code]) {
                    if (check(tmp.bitSum, bitSum[i])) {
                        ans = Math.max(ans, i - tmp.id);
                        found = true;
                    }
                }
                if (!found) hashTable[code].add(new Cow(bitSum[i], i));
            }
        }

        System.out.println(ans);
    }
}
