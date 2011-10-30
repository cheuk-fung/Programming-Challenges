/*
 *  SRC: HDOJ ACM Steps
 * PROB: 相遇周期
 * ALGO: check prime
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
    int gcd(int a, int b)
    {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        int n = in.nextInt();
        while (n-- > 0) {
            String a_str[] = in.next().split("/"),
                   b_str[] = in.next().split("/");
            int a_up   = Integer.parseInt(a_str[0]),
                a_down = Integer.parseInt(a_str[1]),
                a_gcd  = gcd(a_up, a_down),
                b_up   = Integer.parseInt(b_str[0]),
                b_down = Integer.parseInt(b_str[1]),
                b_gcd  = gcd(b_up, b_down);
            a_up   /= a_gcd;
            a_down /= a_gcd;
            b_up   /= b_gcd;
            b_down /= b_gcd;
            int ans_up   = a_up / gcd(a_up, b_up) * b_up,
                ans_down = gcd(a_down, b_down),
                ans_gcd  = gcd(ans_up, ans_down);
            ans_up   /= ans_gcd;
            ans_down /= ans_gcd;
            if (ans_down == 1) out.println(ans_up);
            else out.println(ans_up + "/" + ans_down);
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
