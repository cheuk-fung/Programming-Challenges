/*
 *  SRC: HDOJ ACM Steps
 * PROB: Examining the Rooms
 * ALGO: Stirling numbers of the first kind
 * DATE: Oct 31, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.text.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String args[]) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static DecimalFormat df = new DecimalFormat("0.0000");

    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        BigInteger s[][] = new BigInteger[21][21],
                   f[]   = new BigInteger[21];
        for (int i = 0; i <= 20; i++)
            for (int j = 0; j <= 20; j++)
                s[i][j] = BigInteger.ZERO;

        s[1][1] = BigInteger.ONE;
        for (int i = 2; i <= 20; i++)
            for (int j = 1; j <= i; j++)
                s[i][j] = s[i - 1][j - 1].add(s[i - 1][j].multiply(BigInteger.valueOf(i - 1)));
        f[0] = BigInteger.ONE;
        for (int i = 1; i <= 20; i++) f[i] = f[i - 1].multiply(BigInteger.valueOf(i));

        in.nextInt();
        while (in.hasNext()) {
            BigInteger cnt = BigInteger.ZERO;
            int n = in.nextInt(),
                k = in.nextInt();
            for (int i = 1; i <= k; i++) cnt = cnt.add(s[n][i].subtract(s[n - 1][i - 1]));
            out.println(new BigDecimal(cnt).divide(new BigDecimal(f[n]), 4, RoundingMode.HALF_UP));
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
