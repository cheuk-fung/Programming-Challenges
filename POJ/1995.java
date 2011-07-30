/*
 *  SRC: POJ 1995
 * PROB: Raising Modulo Numbers
 * ALGO: BitInteger
 * DATE: Jul 28, 2011 
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
        int z = cin.nextInt();
        while (z-- != 0) {
            BigInteger m = cin.nextBigInteger();
            int h = cin.nextInt();
            BigInteger ans = BigInteger.ZERO;
            while (h-- != 0) {
                BigInteger a = cin.nextBigInteger(), b = cin.nextBigInteger();
                ans = ans.add(a.modPow(b, m));
            }
            System.out.println(ans.mod(m));
        }
    }
}
