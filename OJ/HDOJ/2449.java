/*
 *  SRC: HDOJ 2449
 * PROB: Gauss Elimination
 * ALGO: Math
 * DATE: Feb 11, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.text.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

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

class GaussElimination {
    private BigFraction[] X;

    //  1: infinitely many solutions
    //  0: one solution
    // -1: no solution
    public int solve(int n, BigFraction[][] A, BigFraction[] B)
    {
        X = new BigFraction[n];

        for (int xc = 0; xc < n; xc++) {
            int row = xc;
            for (int i = row + 1; i < n; i++)
                if (A[i][xc].abs().compareTo(A[row][xc].abs()) > 0) row = i;
            if (A[row][xc].isZero()) {
                if (B[row].isZero()) return 1;
                return -1;
            }

            if (row != xc) {
                for (int j = xc; j < n; j++) {
                    BigFraction tmp = A[xc][j];
                    A[xc][j] = A[row][j];
                    A[row][j] = tmp;
                }
                BigFraction tmp = B[xc];
                B[xc] = B[row];
                B[row] = tmp;
            }

            for (int i = xc + 1; i < n; i++) {
                BigFraction rate = A[i][xc].divide(A[xc][xc]);
                for (int j = xc; j < n; j++)
                    A[i][j] = A[i][j].subtract(rate.multiply(A[xc][j]));
                B[i] = B[i].subtract(rate.multiply(B[xc]));
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            X[i] = B[i];
            for (int j = n - 1; j > i; j--)
                X[i] = X[i].subtract(A[i][j].multiply(X[j]));
            X[i] = X[i].divide(A[i][i]);
        }

        return 0;
    }

    public BigFraction[] getAns() { return X; }

    public String toString()
    {
        String res = "";
        for (int i = 0; i < X.length - 1; i++)
            res += X[i] + " ";
        return res + X[X.length - 1];
    }
}

class Prob {
    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        BigFraction[][] A;
        BigFraction[]   B;

        while (in.hasNext()) {
            int n = in.nextInt();
            A = new BigFraction[n][n];
            B = new BigFraction[n];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    A[i][j] = new BigFraction(in.nextBigInteger(), BigInteger.ONE);
                B[i] = new BigFraction(in.nextBigInteger(), BigInteger.ONE);
            }

            GaussElimination g = new GaussElimination();
            if (g.solve(n, A, B) != 0) out.println("No solution.");
            // else out.println(g.toString().replace(" ", "\n"));
            else {
                BigFraction X[] = g.getAns();
                for (int i = 0; i < n; i++) out.println(X[i]);
            }
            out.println();
        }

        out.flush();
    }
}

class MyReader {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer in;

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

    int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }
    BigInteger nextBigInteger() throws IOException
    {
        return new BigInteger(next());
    }
}
