/*
 *  SRC: HDOJ 3680
 * PROB: Naughty fairies
 * ALGO: Math
 * DATE: Nov 07, 2011 
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
    static final BigInteger TWO = BigInteger.ONE.add(BigInteger.ONE);
    static HashMap<BigInteger, BigInteger> hm = new HashMap<BigInteger, BigInteger>();

    BigInteger dist(BigInteger n, BigInteger m)
    {
        if (hm.containsKey(n)) return hm.get(n);

        BigInteger res;
        if (n.compareTo(m) <= 0) res = m.subtract(n);
        else {
            if (n.mod(TWO).equals(BigInteger.ZERO))
                res = n.subtract(m).min(dist(n.divide(TWO), m).add(BigInteger.ONE));
            else {
                BigInteger nHalf = n.divide(TWO);
                res = n.subtract(m).min(dist(nHalf, m).add(TWO)).min(dist(nHalf.add(BigInteger.ONE), m).add(TWO));
            }
        }

        hm.put(n, res);
        return res;
    }

    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        while (true) {
            BigInteger n = in.nextBigInteger(),
                       m = in.nextBigInteger();
            if (n.equals(BigInteger.ZERO) && m.equals(BigInteger.ZERO)) break;

            hm.clear();
            out.println(dist(n, m));
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

    String next() throws IOException
    {
        while (in == null || !in.hasMoreTokens())
            in = new StringTokenizer(br.readLine());
        return in.nextToken();
    }

    BigInteger nextBigInteger() throws IOException
    {
        return new BigInteger(next());
    }
}
