import java.util.*;
import java.math.BigInteger;

class BigFraction implements Comparable {
    private BigInteger numerator, denominator;
    public static BigFraction ZERO = new BigFraction(BigInteger.ZERO, BigInteger.ONE);
    public static BigFraction ONE  = new BigFraction(BigInteger.ONE,  BigInteger.ONE);

    public BigFraction()
    {
        numerator = BigInteger.ZERO;
        denominator = BigInteger.ONE;
    }

    public BigFraction(int numerator, int denominator)
    {
        this.numerator = BigInteger.valueOf(numerator);
        this.denominator = BigInteger.valueOf(denominator);
    }

    public BigFraction(BigInteger numerator, BigInteger denominator)
    {
        this.numerator = numerator;
        this.denominator = denominator;
    }

    public BigInteger getNumerator()
    {
        return numerator;
    }

    public BigInteger getDenominator()
    {
        return denominator;
    }

    public BigFraction add(BigFraction other)
    {
        BigInteger resNumerator = numerator.multiply(other.denominator).add(other.numerator.multiply(denominator));
        BigInteger resDenominator = denominator.multiply(other.denominator);
        return new BigFraction(resNumerator, resDenominator).simplify();
    }

    public BigFraction subtract(BigFraction other)
    {
        BigInteger resNumerator = numerator.multiply(other.denominator).subtract(other.numerator.multiply(denominator));
        BigInteger resDenominator = denominator.multiply(other.denominator);
        return new BigFraction(resNumerator, resDenominator).simplify();
    }

    public BigFraction multiply(BigFraction other)
    {
        BigInteger resNumerator = numerator.multiply(other.numerator);
        BigInteger resDenominator = denominator.multiply(other.denominator);
        return new BigFraction(resNumerator, resDenominator).simplify();
    }

    public BigFraction divide(BigFraction other)
    {
        BigInteger resNumerator = numerator.multiply(other.denominator);
        BigInteger resDenominator = denominator.multiply(other.numerator);
        return new BigFraction(resNumerator, resDenominator).simplify();
    }

    public BigFraction abs()
    {
        return new BigFraction(numerator.abs(), denominator.abs());
    }

    public int compareTo(Object other)
    {
        return subtract((BigFraction)other).signum();
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
            return new BigFraction(numerator.divide(gcd).negate(), denominator.divide(gcd).negate());
        return new BigFraction(numerator.divide(gcd), denominator.divide(gcd));
    }

    public String toString()
    {
        if (isZero()) return "0";
        if (isInteger()) return numerator.toString();
        return numerator + "/" + denominator;
    }
}
