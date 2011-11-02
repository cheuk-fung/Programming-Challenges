/*
 *  SRC: HDOJ ACM Steps
 * PROB: 一只小蜜蜂...
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
        PrintWriter out = new PrintWriter(System.out);
        Scanner cin = new Scanner(System.in);

        long f[][] = new long[51][51];
        for (int i = 1; i <= 50; i++) {
            f[i][i] = 1;
            for (int j = i + 1; j <= 50; j++)
                f[i][j] = f[i][j - 1] + f[i][j - 2];
        }

        cin.nextInt();
        while (cin.hasNext())
            out.println(f[cin.nextInt()][cin.nextInt()]);


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
