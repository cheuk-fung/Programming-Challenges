/*
 *  SRC: POJ 3080
 * PROB: Blue Jeans
 * ALGO: KMP
 * DATE: Jun 8, 2011 
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

        int n = cin.nextInt();

        while (n-- > 0) new Prob().solve(cin);
    }
}

class Prob
{
    private int[] P = new int[60];

    private void KMPInit(String B, int m)
    {
        P[0] = 0;
        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && B.charAt(j) != B.charAt(i)) j = P[j - 1];
            if (B.charAt(j) == B.charAt(i)) j++;
            P[i] = j;
        }
    }

    private boolean KMP(String A, String B, int n, int m)
    {
        for (int i = 0, j = 0; i < n; i++) {
            while (j > 0 && B.charAt(j) != A.charAt(i)) j = P[j - 1];
            if (B.charAt(j) == A.charAt(i)) j++;
            if (j == m) return true;
        }

        return false;
    }

    public void solve(Scanner cin)
    {
        int m = cin.nextInt();
        String[] dna = new String[m];
        for (int i = 0; i < m; i++) dna[i] = cin.next();

Length:
        for (int l = 3; l <= 61; l++) {
StartPoint:
            for (int i = 0; i + l <= 60; i++) {
                String subStr = dna[0].substring(i, i + l);
                KMPInit(subStr, l);

                for (int j = 1; j < m; j++) {
                    if (KMP(dna[j], subStr, 60, l) == false)
                        continue StartPoint;
                }

                continue Length;
            }

            if (l == 3) {
                System.out.println("no significant commonalities");
                return ;
            }

            String ans = "Z";
            int len = l - 1;
StartPointOfAns:
            for (int i = 0; i + len <= 60; i++) {
                String subStr = dna[0].substring(i, i + len);
                KMPInit(subStr, len);

                for (int j = 1; j < m; j++)
                    if (KMP(dna[j], subStr, 60, len) == false)
                        continue StartPointOfAns;

                if (subStr.compareTo(ans) < 0) ans = subStr;
            }

            System.out.println(ans);

            return ;
        }
    }
}
