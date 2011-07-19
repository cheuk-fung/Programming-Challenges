/*
 *  SRC: NKOJ p1114
 * PROB: Tree Recovery
 * ALGO: Binary Tree
 * DATE: Jul 12, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    private static String postord;

    private static void solve(String preord, String inord)
    {
        if (preord.length() == 0) return ;

        int index = inord.indexOf(preord.charAt(0));

        solve(preord.substring(1, index + 1), inord.substring(0, index));
        solve(preord.substring(index + 1), inord.substring(index + 1));
        postord += preord.charAt(0);
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        while (cin.hasNext()) {
            String preord = cin.next(), inord = cin.next();
            postord = "";
            solve(preord, inord);
            System.out.println(postord);
        }
    }
}

