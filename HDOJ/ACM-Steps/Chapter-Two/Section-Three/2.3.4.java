/*
 *  SRC: HDOJ ACM Steps
 * PROB: Buy the Ticket
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
    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        BigInteger f[] = new BigInteger[201];
        f[0] = BigInteger.ONE;
        for (int i = 1; i <= 200; i++) f[i] = f[i - 1].multiply(BigInteger.valueOf(i));

        int taskCnt = 1;
        while (true) {
            int m = in.nextInt(),
                n = in.nextInt();
            if (m == 0 && n == 0) break;
            out.println("Test #" + taskCnt++ + ":");
            if (n > m) out.println(0);
            else out.println(f[m + n].multiply(BigInteger.valueOf(m - n + 1)).divide(BigInteger.valueOf(m + 1)));
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
