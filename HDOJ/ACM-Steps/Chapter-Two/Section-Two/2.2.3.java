/*
 *  SRC: HDOJ ACM Steps
 * PROB: 汉诺塔VII
 * ALGO: NULL
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
    int a[] = new int[64],
        b[] = new int[64],
        c[] = new int[64];

    boolean check(int p, int a[], int a_cnt, int b[], int b_cnt, int c[], int c_cnt)
    {
        if (p == 0) return true;
        if (b[0] == p) return false;
        if (a[0] == p) {
            for (int i = 0; i < a_cnt - 1; i++)
                a[i] = a[i + 1];
            return check(p - 1, a, a_cnt - 1, c, c_cnt, b, b_cnt);
        }
        if (c[0] == p) {
            for (int i = 0; i < c_cnt - 1; i++)
                c[i] = c[i + 1];
            return check(p - 1, c, c_cnt - 1, a, a_cnt, b, b_cnt);
        }
        return true;
    }

    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        in.nextInt();
        while (in.hasNext()) {
            int n = in.nextInt();
            int a_cnt = in.nextInt();
            for (int i = 0; i < a_cnt; i++)
                a[i] = in.nextInt();
            int b_cnt = in.nextInt();
            for (int i = 0; i < b_cnt; i++)
                b[i] = in.nextInt();
            int c_cnt = in.nextInt();
            for (int i = 0; i < c_cnt; i++)
                c[i] = in.nextInt();

            out.println(check(n, a, a_cnt, b, b_cnt, c, c_cnt));
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
