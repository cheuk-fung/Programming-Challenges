/*
 *  SRC: HDOJ ACM Steps
 * PROB: Fighting for HDU
 * ALGO: NULL
 * DATE: Oct 29, 2011
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    public void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        while (true) {
            int n = in.nextInt();
            if (n == 0) break;

            int a = 0, b = 0;
            int c[] = new int[n],
                j[] = new int[n];
            for (int i = 0; i < n; i++) c[i] = in.nextInt();
            Arrays.sort(c);
            for (int i = 0; i < n; i++) j[i] = in.nextInt();
            Arrays.sort(j);
            for (int i = 0; i < n; i++) {
                if (c[i] > j[i]) a += 2;
                if (c[i] ==j[i]) { a++; b++; }
                if (c[i] < j[i]) b += 2;
            }
            out.println(a + " vs " + b);
            out.flush();
        }
    }
}

class MyReader {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer in;

    boolean hasNext() throws IOException
    {
        if (in.hasMoreTokens()) return true;
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
}
