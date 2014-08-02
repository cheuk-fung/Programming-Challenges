/*
 *  SRC: POJ 1552
 * PROB: Doubles
 * ALGO: NULL
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

        while (new Prob().solve(cin)) ;
    }
}

class Prob
{
    public boolean solve(Scanner cin)
    {
        boolean[] exist = new boolean[200];

        int[] num = new int[20];
        int sum = 0;
        if ((num[sum] = cin.nextInt()) == -1) return false;
        while (num[sum] != 0) {
            exist[num[sum]] = true;
            num[++sum] = cin.nextInt();
        }

        int cnt = 0;
        for (int i = 0; i < sum; i++)
            if (exist[num[i] * 2]) cnt++;

        System.out.println(cnt);

        return true;
    }
}
