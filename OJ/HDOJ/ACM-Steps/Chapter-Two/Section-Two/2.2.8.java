/*
 *  SRC: HDOJ ACM Steps
 * PROB: Big Number
 * ALGO: Math
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

        long f[] = new long[21];
        f[0] = 1;
        for (int i = 1; i < 21; i++) f[i] = f[i - 1] * i;
        for (int i = 0; i < 21; i++) f[i] = (int)Math.log10(f[i]) + 1;

        in.nextInt();
        while (in.hasNext()) {
            int n = in.nextInt();
            if (n < 21) out.println(f[n]);
            else out.println((int)(Math.log10(Math.sqrt(2 * Math.PI * n)) + n * Math.log10(n / Math.E)) + 1);
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
