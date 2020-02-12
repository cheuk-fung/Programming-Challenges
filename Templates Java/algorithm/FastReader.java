package algorithm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class FastReader {

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

    public double[] nextDoubleArray(int length) {
        var a = new double[length];
        for (var i = 0; i < length; i++) {
            a[i] = nextDouble();
        }
        return a;
    }

    public int nextInt() {
        return Integer.valueOf(next());
    }

    public int[] nextIntArray(int length) {
        var a = new int[length];
        for (var i = 0; i < length; i++) {
            a[i] = nextInt();
        }
        return a;
    }

    public long nextLong() {
        return Long.valueOf(next());
    }

    public long[] nextLongArray(int length) {
        var a = new long[length];
        for (var i = 0; i < length; i++) {
            a[i] = nextLong();
        }
        return a;
    }

}
