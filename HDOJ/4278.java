/*
 *  SRC: HDOJ 4278
 * PROB: Faulty Odometer
 * ALGO: NULL
 * DATE: Sep 09, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.*;
import java.math.*;

class Main {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        while (true) {
            String s = cin.next();
            if (s.equals("0")) break;

            String t = "";
            for (char c : s.toCharArray()) {
                if ('0' <= c && c <= '2') t += c;
                else if ('4' <= c && c <= '7') t += (char)(c - 1);
                else t += (char)(c - 2);
            }

            BigInteger r = new BigInteger(t, 8);
            System.out.println(s + ": " + r);
        }
    }
}
