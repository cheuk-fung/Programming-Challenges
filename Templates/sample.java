import java.io.*;
import java.text.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static DecimalFormat df = new DecimalFormat("0.000");

    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        //...

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

    int nextInt() throws IOException { return Integer.parseInt(next()); }
    long nextLong() throws IOException { return Long.parseLong(next()); }
    double nextDouble() throws IOException { return Double.parseDouble(next()); }
    BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }
    BigDecimal nextBigDecimal() throws IOException { return new BigDecimal(next()); }
}
