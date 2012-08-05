import java.util.Scanner;
import java.math.BigInteger;

class Solution {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        BigInteger a = cin.nextBigInteger();
        BigInteger b = cin.nextBigInteger();
        System.out.println(a.pow(b.intValue()).subtract(b.pow(a.intValue())));
    }
}
