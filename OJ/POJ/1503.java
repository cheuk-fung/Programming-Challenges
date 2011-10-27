/*
 *  SRC: POJ 1503
 * PROB: Integer Inquiry
 * ALGO: BigInteger
 * DATE: Jun 10, 2011
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

        BigInteger sum = BigInteger.ZERO;

        while (cin.hasNext()) {
            sum = sum.add(new BigInteger(cin.next()));
        }
        System.out.println(sum);
    }
}
