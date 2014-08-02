/*
 *  SRC: HDOJ ACM Steps
 * PROB: 七夕节
 * ALGO: NULL
 * DATE: Oct 30, 2011 
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

        in.nextInt();
        while (in.hasNext()) {
            int n = in.nextInt();
            int ans = 0;
            for (int i = 2; i <= Math.sqrt(n); i++)
                if (n % i == 0) {
                    ans += i;
                    if (n / i != i) ans += n / i;
                }
            out.println(ans + 1);
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
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }
    long nextLong() throws IOException
    {
        return Long.parseLong(next());
    }
    double nextDouble() throws IOException
    {
        return Double.parseDouble(next());
    }
    BigInteger nextBigInteger() throws IOException
    {
        return new BigInteger(next());
    }
}
