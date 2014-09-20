import java.io.*;
import java.util.*;
import java.math.*;

public class A {
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
        int[] row = new int[n];
        int[] col = new int[n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int cell = in.nextInt();
                row[i] += cell;
                col[j] += cell;
            }

        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (col[j] > row[i]) cnt++;

        out.println(cnt);
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
