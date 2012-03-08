/*
 *  SRC: POJ 2531
 * PROB: Network Saboteur
 * ALGO: Enum
 * DATE: Mar 08, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static final MyReader in = new MyReader();
    static final PrintWriter out = new PrintWriter(System.out);

    void solve() throws IOException
    {
        int n = in.nextInt();
        int[][] c = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                c[i][j] = in.nextInt();
        
        int ans = 0;
        int[] setA = new int[n];
        int[] setB = new int[n];
        for (int bit = 1, loopEnd = 1 << n; bit < loopEnd; bit++) {
            int setACount = 0;
            int setBCount = 0;
            for (int i = 0; i < n; i++) {
                if ((bit & (1 << i)) > 0) {
                    setA[setACount++] = i;
                }
                else {
                    setB[setBCount++] = i;
                }
            }
            
            int curr = 0;
            for (int i = 0; i < setACount; i++)
                for (int j = 0; j < setBCount; j++)
                    curr += c[setA[i]][setB[j]];
            
            ans = Math.max(ans, curr);
        }
        
        out.println(ans);

        out.flush();
    }

    static void debug(Object... x)
    {
        System.out.println(Arrays.deepToString(x));
    }
}

class MyReader {
    static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer in;

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

    BigDecimal nextBigDecimal() throws IOException
    {
        return new BigDecimal(next());
    }
}
