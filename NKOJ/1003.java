/*
 *  SRC: NKOJ 1003
 * PROB: [NKPC1]生成串问题
 * ALGO: NULL
 * DATE: Aug 21, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        String s = cin.next();
        int n = cin.nextInt();
        boolean[][] map = new boolean[256][256];
        int[] cnt = new int[256];
           
        for (int i = 0; i < n; i++) {
            String a = cin.next(), b = cin.next();
            map[a.charAt(0)][b.charAt(0)] = true;
            map[a.charAt(0)][a.charAt(0)] = true;
        }

        for (int k = 0; k < 256; k++)
            for (int i = 0; i < 256; i++)
                for (int j = 0; j < 256; j++)
                    if (map[i][k] && map[k][j]) map[i][j] = true;

        for (int i = 0; i < 256; i++)
            for (int j = 0; j < 256; j++)
                if (map[i][j]) cnt[i]++;

        BigInteger ans = BigInteger.ONE;
        for (int i = 0; i < s.length(); i++)
            if (cnt[s.charAt(i)] > 0) ans = ans.multiply(BigInteger.valueOf(cnt[s.charAt(i)]));

        System.out.println(ans);
    }
}
