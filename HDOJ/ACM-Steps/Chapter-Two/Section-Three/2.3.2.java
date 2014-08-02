/*
 *  SRC: HDOJ ACM Steps
 * PROB: Exponentiation
 * ALGO: BigDecimal
 * DATE: Oct 31, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String args[]) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        while (in.hasNext()) {
            BigDecimal r = in.nextBigDecimal();
            int n = in.nextInt();
            BigDecimal ans = new BigDecimal("1.0");
            while (n-- > 0) ans = ans.multiply(r);
            String ansStr = ans.toPlainString();
            if (ansStr.charAt(0) == '0') ansStr = ansStr.substring(1);
            int back = ansStr.length() - 1;
            while (ansStr.charAt(back) == '0') back--;
            if (ansStr.charAt(back) == '.') back--;
            ansStr = ansStr.substring(0, back + 1);
            out.println(ansStr);
        }

        out.flush();
    }

    void debug(Object...x)
    {
        System.out.println(Arrays.deepToString(x));
    }
}

class MyReader {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer in;

    boolean hasNext() throws IOException
    {
        if (in == null || in.hasMoreTokens()) return true;
        String line = br.readLine();
        if (line == null) return false;
        in = new StringTokenizer(line);
        return true;
    }

    String next() throws IOException
    {
        while (in == null || !in.hasMoreTokens())
            in = new StringTokenizer(br.readLine());
        return in.nextToken();
    }

    int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }
    BigDecimal nextBigDecimal() throws IOException
    {
        return new BigDecimal(next());
    }
}
