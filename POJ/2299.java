/*
 *  SRC: POJ 2299
 * PROB: Ultra-QuickSort
 * ALGO: Merge Sort
 * DATE: Jun 7, 2011 
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

        while (new Prob().solve(cin)) ;
    }
}

class Prob
{
    private int n;
    private long cnt = 0;
    private int[] a;

    public void mergeSort(int l, int r)
    {
        if (l + 1 == r) return ;

        int mid = (l + r) / 2;
        mergeSort(l, mid);
        mergeSort(mid, r);

        int size = 0;
        int[] b = new int[r - l];
        for (int i = l, j = mid; ; ) {
            if (a[i] < a[j]) b[size++] = a[i++];
            else {
                b[size++] = a[j++];
                cnt += mid - i;
            }
            if (i == mid) {
                while (j < r) b[size++] = a[j++];
                break;
            }
            if (j == r) {
                while (i < mid) b[size++] = a[i++];
                break;
            }
        }
        for (int i = 0; i < size; i++) a[l + i] = b[i];
    }

    public boolean solve(Scanner cin)
    {
        n = cin.nextInt();
        if (n == 0) return false;

        a = new int[n];
        for (int i = 0; i < n; i++)
            a[i] = cin.nextInt();

        mergeSort(0, n);

        System.out.println(cnt);

        return true;
    }
}
