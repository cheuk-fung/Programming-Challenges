/*
 *  SRC: NKOJ 2195
 * PROB: Xujie卖车
 * ALGO: DP
 * DATE: Mar 10, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);
    static final int INF = 0x3f3f3f3f;

    int dp(Vector<Integer> v)
    {
        int n = v.size();
        int[] f = new int[n];
        Arrays.fill(f, INF);

        for (int i = 0; i < n; i++) {
            int l = 0, r = n - 1;
            while (l < r) {
                int mid = (l + r - 1) >> 1;
                if (f[mid] <= v.get(i)) l = mid + 1;
                else r = mid;
            }
            f[l] = v.get(i);
        }

        for (int res = n - 1; res >= 0; res--) {
            if (f[res] != INF) return res + 1;
        }

        return 0;
    }

    void solve()
    {
        int n = cin.nextInt();
        Chord[] chords = new Chord[n];
        for (int i = 0; i < n; i++) {
            chords[i] = new Chord(cin.nextInt(), cin.nextInt());
        }
        Arrays.sort(chords);

        int ans = 0;
        for (int i = 0; i + 1 < n; i++) {
            Vector<Integer> v = new Vector<Integer>();
            v.add(chords[i].r);
            for (int j = i + 1; j < n; j++) {
                if (chords[j].l > chords[i].r) break;
                if (chords[j].r >= chords[i].r) {
                    v.add(chords[j].r);
                }
            }
            ans = Math.max(ans, dp(v));
        }

        System.out.println(ans);
    }
}

class Chord implements Comparable {
    int l, r;

    Chord(int l, int r)
    {
        if (l > r) {
            l ^= r;
            r ^= l;
            l ^= r;
        }
        this.l = l;
        this.r = r;
    }

    @Override
    public int compareTo(Object o)
    {
        if (l != ((Chord)o).l) return l - ((Chord)o).l;
        return r - ((Chord)o).r;
    }
}
