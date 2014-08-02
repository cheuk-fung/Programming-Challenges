import java.util.Scanner;
import java.math.BigInteger;

class Solution {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        BigInteger n = cin.nextBigInteger();
        BigInteger l = BigInteger.ONE, r = n;
        BigInteger TWO = BigInteger.valueOf(2);
        while (l.compareTo(r) < 0) {
            BigInteger mid = l.add(r).add(BigInteger.ONE).divide(TWO);
            if (mid.multiply(mid).compareTo(n) <= 0) l = mid;
            else r = mid.subtract(BigInteger.ONE);
        }
        System.out.println(l);
    }
}
