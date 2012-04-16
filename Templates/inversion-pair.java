/*
 *  SRC: NKOJ p1121
 * PROB: Ultra-QuickSort
 * ALGO: Merge Sort
 * DATE: Jun 7, 2011
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
    private long ans = 0;

    public void mergeSort(int a[], int l, int r) // [l, r)
    {
        if (l + 1 == r) return ;

        int mid = (l + r) / 2;
        mergeSort(a, l, mid);
        mergeSort(a, mid, r);

        int b[] = new int[r - l];
        int p = l, q = mid, cnt = 0;
        while (p < mid && q < r) {
            if (a[p] < a[q]) b[cnt++] = a[p++];
            else {
                b[cnt++] = a[q++];
                ans += mid - p;
            }
        }
        while (p < mid) b[cnt++] = a[p++];
        while (q < r)   b[cnt++] = a[q++];

        for (int i = 0; i < cnt; i++) a[l + i] = b[i];
    }

    public void solve()
    {
        Scanner cin = new Scanner(System.in);

        while (true) {
            int n = cin.nextInt();
            if (n == 0) break;

            int a[] = new int[n];
            for (int i = 0; i < n; i++) a[i] = cin.nextInt();

            ans = 0;
            mergeSort(a, 0, n);

            System.out.println(ans);
        }
    }
}
