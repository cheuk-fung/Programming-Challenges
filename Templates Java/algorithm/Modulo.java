package algorithm;

// all a, b < mod
public class Modulo {

    private final long mod;

    public Modulo(long mod) {
        this.mod = mod;
    }

    public long plus(long a, long b) {
        var c = a + b;
        if (c >= mod) {
            c -= mod;
        }
        return c;
    }

    public long minus(long a, long b) {
        var c = a - b;
        if (c < 0) {
            c += mod;
        }
        return c;
    }

    public long times(long a, long b) {
        return a * b % mod;
    }

    public long div(long a, long b) {
        return times(a, pow(b, mod - 2));
    }

    public long pow(long a, long b) {
        long c = 1;

        while (b > 0) {
            if ((b & 1) > 0) {
                c = c * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }

        return c;
    }

    public long combination(int n, int k) {
        return div(factorial(n), times(factorial(k), factorial(n - k)));
    }

    public long combination(int n, int k, long[] factorials) {
        return div(factorials[n], times(factorials[k], factorials[n - k]));
    }

    public long factorial(int n) {
        var f = 1L;
        for (var i = 1; i <= n; i++) {
            f = f * i % mod;
        }
        return f;
    }

    public long[] factorials(int n) {
        var f = new long[n + 1];
        f[0] = 1L;
        for (var i = 1; i <= n; i++) {
            f[i] = f[i - 1] * i % mod;
        }
        return f;
    }

}
