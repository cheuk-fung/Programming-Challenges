/*
 *  SRC: HDOJ ACM Steps
 * PROB: 小数化分数2
 * ALGO: 
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

        in.nextInt();
        while (in.hasNext()) {
            String num = in.next();
            int up, down;
            if (num.indexOf('(') == -1) {
                num = num.substring(2);
                up = Integer.parseInt(num);
                down = (int)Math.pow(10, num.length());
            }
            else {
                String ring = num.substring(num.indexOf('(') + 1, num.length() - 1),
                       num2 = num.substring(2, num.indexOf('(')) + ring;
                int e = num.length() - ring.length() - 4;
                num = num.substring(2, num.indexOf('('));
                if (num.equals("")) num = "0";
                int a = Integer.parseInt(num),
                    b = Integer.parseInt(num2);
                up = b - a;
                down = (int)(Math.pow(10, num2.length()) - Math.pow(10, e));
            }
            out.println(up / gcd(up, down) + "/" + down / gcd(up, down));
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
