/*
 *  SRC: HDOJ ACM Steps
 * PROB: Joseph
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

        int k,
            ans[] = new int[14];
        for (k = 1; k < 14; k++) {
            int m = k;
            while (ans[k] == 0) {
                m++;
                int r = 2 * k;
                for (int p = 0; r > k; r--) {
                    p = (p + m - 1) % r;
                    if (p < k) break;
                }
                if (r == k) ans[k] = m;
            }
        }

        while (true) {
            k = in.nextInt();
            if (k == 0) break;
            out.println(ans[k]);
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
