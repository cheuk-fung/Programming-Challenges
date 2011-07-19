/*
 *  SRC: POJ 2019
 * PROB: Power of Cryptography
 * ALGO: Bisection
 * DATE: Jul 18, 2011 
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
        while (cin.hasNext()) {
            int n = cin.nextInt();
            BigInteger p = cin.nextBigInteger();

            int low = 0, high = 0x3FFFFFFF;
            while (low < high) {
                int mid = (low + high - 1) / 2;
                if (BigInteger.valueOf(mid).pow(n).compareTo(p) >= 0) high = mid;
                else low = mid + 1;
            }

            if (BigInteger.valueOf(low).pow(n).compareTo(p) > 0) low--;
            System.out.println(low);
        }
    }
}
