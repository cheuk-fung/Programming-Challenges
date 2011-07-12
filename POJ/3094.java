/*
 *  SRC: POJ 3094
 * PROB: Quicksum
 * ALGO: NUll
 * DATE: Jul 12, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    private static int solve(String packet)
    {
        int res = 0;
        
        for (int i = 0; i < packet.length(); i++) {
            if (packet.charAt(i) == ' ') continue;
            res += (packet.charAt(i) - 'A' + 1) * (i + 1);
        }

        return res;
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        while (1 + 1 == 2) {
            String s = cin.nextLine();
            if (s.equals("#")) break;
            System.out.println(solve(s));
        }
    }
}
