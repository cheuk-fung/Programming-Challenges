package algorithm;

// all a, b < mod
public class Modulo {

    private final long mod;

    public Modulo(long mod) {
        this.mod = mod;
    }

    // a + b
    public long add(long a, long b) {
        var c = a + b;
        if (c >= mod) {
            c -= mod;
        }
        return c;
    }

    // a - b
    public long subtract(long a, long b) {
        var c = a - b;
        if (c < 0) {
            c += mod;
        }
        return c;
    }

    // a * b
    public long multiply(long a, long b) {
        return a * b % mod;
    }

    // a ^ b
    public long power(long a, long b) {
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

    // a / b
    public long divide(long a, long b) {
        return multiply(a, power(b, mod - 2));
    }

}
