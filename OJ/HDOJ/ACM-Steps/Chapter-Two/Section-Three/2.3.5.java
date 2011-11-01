/*
 *  SRC: HDOJ ACM Steps
 * PROB: Count the Trees 
 * ALGO: Catalan number
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

        BigInteger c[] = new BigInteger[101];
        c[0] = BigInteger.ONE;
        for (int i = 1; i <= 100; i++)
            c[i] = c[i - 1].multiply(BigInteger.valueOf(2 * (2 * i - 1))).divide(BigInteger.valueOf((i + 1)));

        BigInteger f[] = new BigInteger[101];
        f[0] = BigInteger.ONE;
        for (int i = 1; i <= 100; i++)
            f[i] = f[i - 1].multiply(BigInteger.valueOf(i));

        for (int i = 0; i <= 100; i++)
            c[i] = c[i].multiply(f[i]);

        while (in.hasNext()) {
            int n = in.nextInt();
            if (n == 0) break;
            out.println(c[n]);
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
}
