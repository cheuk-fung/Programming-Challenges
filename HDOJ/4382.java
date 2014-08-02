/*
 *  SRC: HDOJ 4382
 * PROB: Harry Potter and Cyber Sequence Generator
 * ALGO: Matrix
 * DATE: Aug 22, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

class Main {
    static final int MOD = 1000000007;

    int[][] multiply(int[][] A, int [][] B)
    {
        int[][] R = new int[3][3];
        int n = A.length, m = A[0].length, q = B[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < q; j++) {
                for (int k = 0; k < m; k++) {
                    R[i][j] = (int)((R[i][j] + (long)A[i][k] * B[k][j]) % MOD);
                }
            }
        }

        return R;
    }

    void run()
    {
        Scanner cin = new Scanner(System.in);
        int tasks = cin.nextInt();
        for (int task = 1; task <= tasks; task++) {
            System.out.println("Case " + task + ":");

            int[][] A = { {cin.nextInt(), 0, 1} };
            int[][] B = {
                {1, 0, 0},
                {0, 1, 0},
                {0, 0, 1}
            };
            int[][] C;
            String s;
            while (!(s = cin.next()).equals("END")) {
                int dest = cin.next().charAt(1) - '0' - 1;
                String src = cin.next();
                C = new int[3][3];
                C[dest ^ 1][dest ^ 1] = 1;
                C[2][2] = 1;
                if (s.equals("MUL")) {
                    C[dest][dest] = Integer.parseInt(src);
                } else {
                    if (src.charAt(0) == 'C') {
                        C[src.charAt(1) - '0' - 1][dest] = 1;
                    } else {
                        C[2][dest] = Integer.parseInt(src);
                    }
                }
                if (s.equals("ADD")) {
                    C[dest][dest]++;
                }
                B = multiply(B, C);
            }

            int q = cin.nextInt();
            while (q-- > 0) {
                BigInteger n = cin.nextBigInteger();
                int[][] R = A.clone();
                int[][] M = B.clone();
                while (!n.equals(BigInteger.ZERO)) {
                    if (n.and(BigInteger.ONE).equals(BigInteger.ONE)) {
                        R = multiply(R, M);
                    }
                    M = multiply(M, M);
                    n = n.shiftRight(1);
                }

                System.out.println(R[0][1]);
            }
        }
    }

    public static void main(String[] args)
    {
        new Main().run();
    }
}
