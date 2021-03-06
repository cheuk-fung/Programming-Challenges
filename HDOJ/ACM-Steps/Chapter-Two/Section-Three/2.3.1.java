/*
 *  SRC: HDOJ ACM Steps
 * PROB: A + B Problem II
 * ALGO: BigInteger
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

        int n = in.nextInt();
        for (int task = 1; task <= n; task++) {
            BigInteger a = in.nextBigInteger(),
                       b = in.nextBigInteger();
            out.println("Case " + task + ":");
            out.println(a + " + " + b + " = " + a.add(b));
            if (task != n) out.println();
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

    BigInteger nextBigInteger() throws IOException
    {
        return new BigInteger(next());
    }
}
