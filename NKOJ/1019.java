/*
 *  SRC: NKOJ P1019
 * PROB: 计算 A+B (超级大数相加)
 * ALGO: BigInteger
 * DATE: Jul 12, 2011 
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

        BigInteger a = new BigInteger(cin.next()), b = new BigInteger(cin.next());

        System.out.println(a.add(b));
    }
}
