/*
 *  SRC: HDOJ ACM Steps
 * PROB: As Easy As A+B
 * ALGO: sort
 * DATE: Oct 29, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int n = cin.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = cin.nextInt();
            Arrays.sort(a);
            System.out.print(a[0]);
            for (int i = 1; i < n; i++) System.out.print(" " + a[i]);
            System.out.println();
        }
    }
}
