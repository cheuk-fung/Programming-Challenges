/*
 *  SRC: POJ 1836
 * PROB: Alignment
 * ALGO: DP
 * DATE: Mar 16, 2012
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
    static final double INF = 1e10;

    int lowerBound(Double[] a, double v)
    {
        int l = 0, r = a.length - 1;
        while (l < r) {
            int mid = (l + r - 1) >> 1;
            if (a[mid] < v) l = mid + 1;
            else r = mid;
        }
        return l;
    }

    int[] lis(Double[] a)
    {
        int[] f = new int[a.length];
        Double[] g = new Double[a.length];
        Arrays.fill(g, INF);
        for (int i = 0; i < a.length; i++) {
            int j = lowerBound(g, a[i]);
            f[i] = j + 1;
            g[j] = a[i];
        }

        return f;
    }

    void solve()
    {
        int n = cin.nextInt();
        Double[] height = new Double[n];
        double maxHeight = 0;
        for (int i = 0; i < n; i++) {
            height[i] = cin.nextDouble();
            maxHeight = Math.max(maxHeight, height[i]);
        }

        int left = 0;
        while (height[left] != maxHeight) {
            left++;
        }

        int[] f = lis(height);
        Collections.reverse(Arrays.asList(height));
        int[] g = lis(height);

        int right = 0;
        while (height[right] != maxHeight) {
            right++;
        }

        int ans = 0x3f3f3f3f;
        for (int i = 0; i < n; i++) {
            ans = Math.min(ans, n - (f[i] + g[n - i - 1] - 1));
        }

        if (left + right != n - 1) {
            ans = Math.min(ans, n - (f[left] + g[right]));
        }

        System.out.println(ans);
    }
}
