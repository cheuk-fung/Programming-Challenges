/*
 *  SRC: POJ 1080
 * PROB: Human Gene Functions
 * ALGO: DP
 * DATE: Mar 17, 2012
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
    static final int[][] score = new int[256][256];
    static {
        score['A']['A'] = 5;
        score['A']['C'] = -1;
        score['A']['G'] = -2;
        score['A']['T'] = -1;
        score['A'][' '] = -3;

        score['C']['A'] = -1;
        score['C']['C'] = 5;
        score['C']['G'] = -3;
        score['C']['T'] = -2;
        score['C'][' '] = -4;

        score['G']['A'] = -2;
        score['G']['C'] = -3;
        score['G']['G'] = 5;
        score['G']['T'] = -2;
        score['G'][' '] = -2;

        score['T']['A'] = -1;
        score['T']['C'] = -2;
        score['T']['G'] = -2;
        score['T']['T'] = 5;
        score['T'][' '] = -1;

        score[' ']['A'] = -3;
        score[' ']['C'] = -4;
        score[' ']['G'] = -2;
        score[' ']['T'] = -1;
        score[' '][' '] = 0;
    }

    void solve()
    {
        int tasks = cin.nextInt();
        for ( ; tasks > 0; tasks--) {
            cin.nextInt();
            String a = cin.next();
            cin.nextInt();
            String b = cin.next();

            int[][] f = new int[a.length() + 1][b.length() + 1];
            for (int i = 1; i <= a.length(); i++) {
                f[i][0] = f[i - 1][0] + score[a.charAt(i - 1)][' '];
            }
            for (int j = 1; j <= b.length(); j++) {
                f[0][j] = f[0][j - 1] + score[' '][b.charAt(j - 1)];
            }
            for (int i = 1; i <= a.length(); i++) {
                for (int j = 1; j <= b.length(); j++) {
                    f[i][j] = Math.max(Math.max(f[i - 1][j] + score[a.charAt(i - 1)][' '],
                                                f[i][j - 1] + score[' '][b.charAt(j - 1)]),
                                       f[i - 1][j - 1] + score[a.charAt(i - 1)][b.charAt(j - 1)]);
                }
            }

            System.out.println(f[a.length()][b.length()]);
        }
    }
}
