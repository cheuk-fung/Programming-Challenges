/*
 *  SRC: POJ 1200
 * PROB: Crazy Search
 * ALGO: Hash
 * DATE: Jul 19, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;
import java.util.HashMap;

class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        int n = cin.nextInt(), nc = cin.nextInt();
        String s = cin.next();
        HashMap<String, Boolean> hm = new HashMap<String, Boolean>();

        int cnt = 0;
        for (int i = 0; i < s.length() - n + 1; i++) {
            String key = s.substring(i, i + n);
            if (hm.containsKey(key) == false) {
                hm.put(key, true);
                cnt++;
            }
        }

        System.out.println(cnt);
    }
}
