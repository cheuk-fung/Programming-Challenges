/*
 *  SRC: HDOJ ACM Steps
 * PROB: Fibonacci
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

        int f[] = new int[30];
        f[0] = 0;
        f[1] = 1;
        for (int i = 2; i < 30; i++)
            f[i] = f[i - 2] + f[i - 1];
        for (int i = 2; i < 30; i++)
            while (f[i] >= 10000) f[i] /= 10;

        // proximately, f[n]=(((1+sqrt(5))/2)^n-((1-sqrt(5))/2)^n)/sqrt(5)
        // thus, log10(f[n])=n*log10((1+sqrt(5))/2)+log10(1-((1-sqrt(5))/(1+sqrt(5)))^n)-log10(sqrt(5));
        // log10(1-((1-sqrt(5))/(1+sqrt(5)))^n)->0, when n->infinite
        // hence, log10(f[n])=n*log10((1+sqrt(5))/2)-log10(5)/2;
        // let e=log10(f[n])=floor(e)+{e}
        // so, f[n]=10^e=10^(floor(e)+{e})=10^{e}*10^floor(e)
        // hence, the first four digits of f[n] is floor(10^{e} * 1000);

        double x = (Math.sqrt(5) + 1) / 2;
        while (in.hasNext()) {
            int n = in.nextInt();
            if (n < 30) out.println(f[n]);
            else {
                double e = n * Math.log10(x) - Math.log10(5) / 2;
                out.println((int)(Math.pow(10, e - (long)e) * 1000));
            }
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
