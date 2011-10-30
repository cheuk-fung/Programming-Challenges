/*
 *  SRC: HDOJ ACM Steps
 * PROB: Largest prime factor
 * ALGO: prime
 * DATE: Oct 30, 2011 
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
    static final int maxN = 1000000;
    int p[], pos[];
    boolean b[];

    int getPrime(int n)
    {
        p = new int[n];
        pos = new int[n];
        b = new boolean[n];

        int cnt = 0;
        for (int i = 0; i < n; i++)
            b[i] = true;
        b[0] = b[1] = false;
        for (int i = 2; i < n; i++) {
            if (b[i]) {
                pos[i] = cnt;
                p[cnt++] = i;
            }
            for (int j = 0; j < cnt && i * p[j] < n; j++) {
                b[i * p[j]] = false;
                if (i % p[j] == 0) break;
            }
        }

        return cnt;
    }

    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        int prmCnt = getPrime(maxN);

        while (in.hasNext()) {
            int n = in.nextInt();
            if (n == 1) {
                out.println(0);
                continue;
            }
            int maxFrac = 0;
            for (int i = 0; p[i] <= Math.sqrt(n) && i < prmCnt; i++)
                if (n % p[i] == 0) {
                    maxFrac = p[i];
                    while (n % p[i] == 0) n /= p[i];
                }
            maxFrac = Math.max(maxFrac, n);
            out.println(pos[maxFrac] + 1);
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
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }
    long nextLong() throws IOException
    {
        return Long.parseLong(next());
    }
    double nextDouble() throws IOException
    {
        return Double.parseDouble(next());
    }
    BigInteger nextBigInteger() throws IOException
    {
        return new BigInteger(next());
    }
}
