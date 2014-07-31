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
    static final MyReader in = new MyReader();
    static final PrintWriter out = new PrintWriter(System.out);

    final int MAXBIT = 22;
    final int MAXNUM = 1 << MAXBIT;


    void solve() throws IOException
    {
        while (in.hasNext()) {
            int n = in.nextInt();
            int[] a = new int[n];
            int[] f = new int[MAXNUM];
            Arrays.fill(f, -1);
            for (int i = 0; i < n; i++) {
                a[i] = in.nextInt();
                f[a[i] ^ ((1 << MAXBIT) - 1)] = a[i];
            }

            for (int i = (1 << MAXBIT) - 1; i >= 0; i--) {
                if (f[i] == -1) {
                    for (int j = 0; j < MAXBIT; j++) {
                        if (f[i | (1 << j)] != -1) {
                            f[i] = f[i | (1 << j)];
                            break;
                        }
                    }
                }
            }

            for (int i = 0; i < n; i++) {
                out.print(f[a[i]] + " ");
            }
            out.println();
        }

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
