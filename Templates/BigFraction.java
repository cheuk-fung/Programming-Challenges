import java.math.BigInteger;

class BigFraction {
    private BigInteger numerator, denominator;
    public static BigFraction ZERO = new BigFraction(BigInteger.ZERO, BigInteger.ONE);
    public static BigFraction ONE  = new BigFraction(BigInteger.ONE,  BigInteger.ONE);

    public BigFraction()
    {
        numerator = BigInteger.ZERO;
        denominator = BigInteger.ONE;
    }

    public BigFraction(BigInteger _numerator, BigInteger _denominator)
    {
        numerator = _numerator;
        denominator = _denominator;
    }

    public BigFraction add(BigFraction other)
    {
        BigInteger new_numerator = numerator.multiply(other.denominator).add(other.numerator.multiply(denominator));
        BigInteger new_denominator = denominator.multiply(other.denominator);
        return new BigFraction(new_numerator, new_denominator).simplify();
    }

    public BigFraction subtract(BigFraction other)
    {
        BigInteger new_numerator = numerator.multiply(other.denominator).subtract(other.numerator.multiply(denominator));
        BigInteger new_denominator = denominator.multiply(other.denominator);
        return new BigFraction(new_numerator, new_denominator).simplify();
    }

    public BigFraction multiply(BigFraction other)
    {
        BigInteger new_numerator = numerator.multiply(other.numerator);
        BigInteger new_denominator = denominator.multiply(other.denominator);
        return new BigFraction(new_numerator, new_denominator).simplify();
    }

    public BigFraction divide(BigFraction other)
    {
        BigInteger new_numerator = numerator.multiply(other.denominator);
        BigInteger new_denominator = denominator.multiply(other.numerator);
        return new BigFraction(new_numerator, new_denominator).simplify();
    }

    public BigFraction abs()
    {
        return new BigFraction(numerator.abs(), denominator.abs());
    }

    public int compareTo(BigFraction other)
    {
        return subtract(other).signum();
    }

    public boolean isZero()
    {
        return numerator.equals(BigInteger.ZERO);
    }

    public boolean isInteger()
    {
        return denominator.equals(BigInteger.ONE);
    }

    public BigFraction negate()
    {
        return new BigFraction(numerator.negate(), denominator);
    }

    public int signum()
    {
        return numerator.signum();
    }

    public BigFraction simplify()
    {
        if (isZero()) return BigFraction.ZERO;
        BigInteger gcd = numerator.gcd(denominator);
        if (denominator.signum() == -1)
            return new BigFraction(numerator.divide(gcd).negate(),
                    denominator.divide(gcd).negate());
        return new BigFraction(numerator.divide(gcd), denominator.divide(gcd));
    }

    public String toString()
    {
        if (isZero()) return "0";
        if (isInteger()) return numerator.toString();
        return numerator + "/" + denominator;
    }
}
