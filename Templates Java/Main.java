import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.*;
import java.util.*;
import java.util.function.*;

public class Main {

    private static final FastReader in = new FastReader();
    private static final PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        var t = in.nextInt();
        while (t-- > 0) {
            solve();
        }

        out.flush();
    }

    private void solve() {
    }

    @SuppressWarnings("unused")
    private static void debug(String name, Object o) {
        String value = Arrays.deepToString(new Object[] { o });
        value = value.substring(1, value.length() - 1);
        System.err.println(name + " => " + value);
    }

    @SuppressWarnings("unused")
    private static int binarySearch(int left, int right, Predicate<Integer> leftShouldAdvance) {
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (leftShouldAdvance.test(mid)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

}

class FastReader {

    private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    private static StringTokenizer in;

    public String next() {
        while (in == null || !in.hasMoreTokens()) {
            try {
                in = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                return null;
            }
        }
        return in.nextToken();
    }

    public BigDecimal nextBigDecimal() {
        return new BigDecimal(next());
    }

    public BigInteger nextBigInteger() {
        return new BigInteger(next());
    }

    public boolean nextBoolean() {
        return Boolean.valueOf(next());
    }

    public byte nextByte() {
        return Byte.valueOf(next());
    }

    public double nextDouble() {
        return Double.valueOf(next());
    }

    public int nextInt() {
        return Integer.valueOf(next());
    }

    public long nextLong() {
        return Long.valueOf(next());
    }

}
