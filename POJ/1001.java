/*
 *  SRC: POJ 1001
 * PROB: Exponentiation
 * ALGO: NULL
 * DATE: Sep 19, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.Scanner;
import java.math.BigDecimal;

class Main {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            BigDecimal R = cin.nextBigDecimal();
            int n = cin.nextInt();
            String str = R.pow(n).toPlainString();
            if (str.startsWith("0")) str = str.split("^0")[1];
            if (str.contains(".")) {
                while (str.endsWith("0")) str = str.split("0$")[0];
            }
            str = str.split("\\.$")[0];
            System.out.println(str);
        }
    }
}
