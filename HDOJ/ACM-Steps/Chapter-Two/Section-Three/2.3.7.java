/*
 *  SRC: HDOJ ACM Steps
 * PROB: 下沙的沙子有几粒？
 * ALGO: Combinatorics
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
    BigInteger f[] = new BigInteger[41];

    BigInteger c(int n, int m)
    {
        return f[n].divide(f[m]).divide(f[n - m]);
    }

    void solve() throws IOException
    {
        PrintWriter out = new PrintWriter(System.out);
        Scanner cin = new Scanner(System.in);

        f[0] = BigInteger.ONE;
        for (int i = 1; i <= 40; i++) f[i] = f[i - 1].multiply(BigInteger.valueOf(i));

        while (cin.hasNext()) {
            int m = cin.nextInt(),
                n = cin.nextInt();
            out.println(c(m + n, n).subtract(c(m + n, m + 1)));
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
