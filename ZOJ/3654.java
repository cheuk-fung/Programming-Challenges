/*
 *  SRC: ZOJ 3654
 * PROB: Letty's Math Class
 * ALGO: Implementation
 * DATE: Sep 29, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
    public static final void main(String[] args)
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        while (true) {
            try {
                String expr = br.readLine();
                String sections[] = br.readLine().split(" ");
                BigInteger A = new BigInteger(sections[0]);
                BigInteger B = new BigInteger(sections[1]);
                BigInteger C = calcExpr(expr);
                if (A.equals(BigInteger.valueOf(9))) {
                    out.println("A");
                } else if (B.equals(BigInteger.valueOf(9))) {
                    out.println("B");
                } else if (A.equals(C)) {
                    out.println("B");
                } else {
                    out.println("A");
                }
            } catch (Exception e) {
                break;
            }
        }
        out.flush();
    }

    private static BigInteger calcExpr(String expr)
    {
        BigInteger res = BigInteger.ZERO;
        String num = "";
        int sign = 1;
        for (char c : expr.toCharArray()) {
            if (c == '+' || c == '-') {
                if (sign == 1) res = res.add(new BigInteger(num));
                else res = res.subtract(new BigInteger(num));
                num = "";
                sign = c == '+' ? 1 : -1;
            } else {
                num = num + c;
            }
        }
        if (!num.equals("")) {
            if (sign == 1) res = res.add(new BigInteger(num));
            else res = res.subtract(new BigInteger(num));
        }
        return res;
    }
}
