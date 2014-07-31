import java.io.*;
import java.util.*;
import java.math.*;

public class B {
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
        double[] r = new double[n];
        for (int i = 0; i < n; i++) r[i] = in.nextDouble();
        Arrays.sort(r);
        double ans = 0.0;
        for (int i = n - 1, red = 1; i >= 0; i--, red ^= 1) {
            if (red == 1) ans += Math.PI * r[i] * r[i];
            else ans -= Math.PI * r[i] * r[i];
        }

        out.println(ans);
        out.flush();
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

    int nextInt() throws IOException { return Integer.parseInt(next()); }
    long nextLong() throws IOException { return Long.parseLong(next()); }
    double nextDouble() throws IOException { return Double.parseDouble(next()); }
    BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }
    BigDecimal nextBigDecimal() throws IOException { return new BigDecimal(next()); }
}
