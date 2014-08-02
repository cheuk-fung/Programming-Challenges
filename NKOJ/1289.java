/*
 *  SRC: NKOJ 1289
 * PROB: Bignum Arithmetic
 * ALGO: BigInteger
 * DATE: Aug 24, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.math.BigInteger;

class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            BigInteger a = cin.nextBigInteger(),
                       b = cin.nextBigInteger();
            System.out.println(a.multiply(b));
        }
    }
}
