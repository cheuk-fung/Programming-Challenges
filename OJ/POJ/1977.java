/*
 *  SRC: POJ 1977
 * PROB: Odd Loving Bakers
 * ALGO: Matrix
 * DATE: Oct 08, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

import java.util.HashMap;
import java.util.Scanner;

class Main {
    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        Scanner cin = new Scanner(System.in);
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int n = cin.nextInt();
            int m = cin.nextInt();

            int[][] mark = new int[1][n];
            int[][] mat = new int[n][n];
            HashMap<String, Integer> idx = new HashMap<String, Integer>();
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                String name = cin.next();
                if (!idx.containsKey(name)) idx.put(name, cnt++);
                int u = idx.get(name);
                mark[0][u] = cin.nextInt() & 1;
                int k = cin.nextInt();
                for (int j = 0; j < k; j++) {
                    String favorite = cin.next();
                    if (!idx.containsKey(favorite)) idx.put(favorite, cnt++);
                    int v = idx.get(favorite);
                    mat[u][v] = 1;
                }
            }
            for (int i = 0; i < n; i++) mat[i][i]++;

            for (m--; m > 0; m >>= 1) {
                if ((m & 1) == 1) mark = multiply(mark, mat);
                mat = multiply(mat, mat);
            }

            int ans = 0;
            for (int i = 0; i < n; i++) {
                if (mark[0][i] == 1) ans++;
            }
            System.out.println(ans);
        }
    }

    private int[][] multiply(int[][] A, int[][] B)
    {
        int n = A.length, l = B.length, m = B[0].length;
        int[][] R = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < l; k++) {
                    R[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                R[i][j] &= 1;
            }
        }
        return R;
    }
}
