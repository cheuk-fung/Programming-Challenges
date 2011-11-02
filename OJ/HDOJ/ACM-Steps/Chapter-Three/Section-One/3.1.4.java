/*
 *  SRC: HDOJ ACM Steps
 * PROB: 母牛的故事
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

        int f[] = new int[55];
        f[0] = 0;
        f[1] = 1;
        f[2] = 2;
        f[3] = 3;
        for (int i = 4; i < 55; i++) f[i] = f[i - 1] + f[i - 3];

        while (true) {
            int n = in.nextInt();
            if (n == 0) break;
            out.println(f[n]);
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
