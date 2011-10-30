/*
 *  SRC: HDOJ ACM Steps
 * PROB: 最小公倍数
 * ALGO: gcd
 * DATE: Oct 30, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;
import java.math.BigInteger;

class Main {
    public static void main(String args[])
    {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            BigInteger a = new BigInteger(cin.next()),
                       b = new BigInteger(cin.next());
            System.out.println(a.multiply(b).divide(a.gcd(b)));
        }
    }
}
