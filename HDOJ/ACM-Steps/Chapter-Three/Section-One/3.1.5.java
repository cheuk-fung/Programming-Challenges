/*
 *  SRC: HDOJ ACM Steps
 * PROB: 折线分割平面
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
    int calc(int n)
    {
        return 2 * n * n - n + 1;
    }

    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        in.nextInt();
        while (in.hasNext())
            out.println(calc(in.nextInt()));

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
