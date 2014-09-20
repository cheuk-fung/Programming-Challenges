import java.io.*;
import java.util.*;
import java.math.*;

public class E {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static MyReader in = new MyReader();
    static PrintWriter out = new PrintWriter(System.out);

    void solve() throws IOException
    {
        int n = in.nextInt(),
            m = in.nextInt();

        long[] powers = new long[n];
        powers[0] = 1;
        for (int i = 1; i < n; i++)
            powers[i] = powers[i - 1] * 97;

        long[] hashInclude = new long[n];
        long[] hashExclude = new long[n];
        for (int i = 0; i < n; i++)
            hashInclude[i] += powers[i];
        for (int i = 0; i < m; i++) {
            int u = in.nextInt() - 1,
                v = in.nextInt() - 1;
            hashInclude[u] += powers[v];
            hashInclude[v] += powers[u];
            hashExclude[u] += powers[v];
            hashExclude[v] += powers[u];
        }
        Arrays.sort(hashInclude);
        Arrays.sort(hashExclude);

        long ans = 0, countInclude = 1, countExclude = 1;
        for (int i = 1; i < n; i++) {
            if (hashInclude[i] == hashInclude[i - 1]) countInclude++;
            else {
                ans += countInclude * (countInclude - 1) / 2;
                countInclude = 1;
            }

            if (hashExclude[i] == hashExclude[i - 1]) countExclude++;
            else {
                ans += countExclude * (countExclude - 1) / 2;
                countExclude = 1;
            }
        }
        ans += countInclude * (countInclude - 1) / 2;
        ans += countExclude * (countExclude - 1) / 2;
        out.println(ans);

        out.flush();
    }
}

class MyReader {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
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
