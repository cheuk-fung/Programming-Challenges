/*
 *  SRC: HDOJ ACM Steps
 * PROB: Children’s Queue
 * ALGO: DP
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

        BigInteger f[] = new BigInteger[1001];
        f[0] = f[1] = BigInteger.ONE;
        f[2] = BigInteger.valueOf(2);
        f[3] = BigInteger.valueOf(4);
        for (int i = 4; i <= 1000; i++) {
            /*
             * f[i] = f[i - 1].add(BigInteger.ONE);
             * for (int j = 3; j <= i; j++)
             *     f[i] = f[i].add(f[i - j]);
             *
             * it equals the following one
             */
            f[i] = f[i - 1].add(f[i - 2]).add(f[i - 4]);
        }

        while (in.hasNext())
            out.println(f[in.nextInt()]);

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
