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
    public static void main(String args[]) throws IOException
    {
        new Prob().solve();
    }
}

class Fraction {
    BigInteger up, down;

    Fraction()
    {
        up = BigInteger.ZERO;
        down = BigInteger.ZERO;
    }

    Fraction(BigInteger _up, BigInteger _down)
    {
        up = _up;
        down = _down;
    }

    public String toString()
    {
        if (isZero()) return "0";

        if (down.compareTo(BigInteger.ZERO) < 0) {
            up = up.multiply(BigInteger.valueOf(-1));
            down = down.multiply(BigInteger.valueOf(-1));
        }

        if (down.equals(BigInteger.ONE)) return up.toString();
        return up + "/" + down;
    }

    boolean isZero()
    {
        return up.equals(BigInteger.ZERO);
    }

    Fraction simplify()
    {
        if (isZero()) return this;
        BigInteger gcd = up.gcd(down);
        return new Fraction(up.divide(gcd), down.divide(gcd));
    }

    Fraction add(Fraction other)
    {
        BigInteger new_up = up.multiply(other.down).add(other.up.multiply(down));
        BigInteger new_down = down.multiply(other.down);
        return new Fraction(new_up, new_down).simplify();
    }

    Fraction subtract(Fraction other)
    {
        BigInteger new_up = up.multiply(other.down).subtract(other.up.multiply(down));
        BigInteger new_down = down.multiply(other.down);
        return new Fraction(new_up, new_down).simplify();
    }

    Fraction multiply(Fraction other)
    {
        BigInteger new_up = up.multiply(other.up);
        BigInteger new_down = down.multiply(other.down);
        return new Fraction(new_up, new_down).simplify();
    }

    Fraction divide(Fraction other)
    {
        BigInteger new_up = up.multiply(other.down);
        BigInteger new_down = down.multiply(other.up);
        return new Fraction(new_up, new_down).simplify();
    }
}

class Prob {
    void solve() throws IOException
    {
        //MyReader in = new MyReader();
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);

        Fraction a[][] = new Fraction[200][200],
                 b[]   = new Fraction[200],
                 ans[] = new Fraction[200];

        /*
        Fraction aa[][] = new Fraction[200][200],
                 bb[] = new Fraction[200],
                 */

CaseLoop:
        while (in.hasNext()) {
            int n = in.nextInt();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    a[i][j] = new Fraction(in.nextBigInteger(), BigInteger.ONE);
                b[i] = new Fraction(in.nextBigInteger(), BigInteger.ONE);
            }

            /*
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    aa[i][j] = a[i][j];
                bb[i] = b[i];
            }

            for (int ii = 0; ii < n; ii++) {
                for (int jj = 0; jj < n; jj++)
                    out.print(a[ii][jj] + " ");
                out.println(b[ii]);
            }
            */

            int pos[] = new int[n];
            for (int i = 0; i < n; i++) pos[i] = i;
            for (int j = 0; j < n; j++) {
                boolean flag = true;
                for (int i = j; i < n; i++)
                    if (!a[pos[i]][j].isZero()) {
                        flag = false;

                        int tmp = pos[i];
                        pos[i] = pos[j];
                        pos[j] = tmp;

                        for (int k = i + 1; k < n; k++) {
                            Fraction t = a[pos[k]][j].divide(a[pos[j]][j]);
                            for (int l = j; l < n; l++)
                                a[pos[k]][l] = a[pos[k]][l].subtract(t.multiply(a[pos[j]][l]));
                            b[pos[k]] = b[pos[k]].subtract(t.multiply(b[pos[j]]));
                        }

                        break;
                    }

                /*
                for (int ii = 0; ii < n; ii++) {
                    for (int jj = 0; jj < n; jj++)
                        out.print(a[ii][jj] + " ");
                    out.println(b[ii]);
                }
                */

                if (flag) {
                    out.println("No solution.");
                    out.println();
                    continue CaseLoop;
                }
            }

            for (int i = n - 1; i >= 0; i--) {
                ans[i] = b[pos[i]];
                for (int j = i + 1; j < n; j++)
                    ans[i] = ans[i].subtract(a[i][j].multiply(ans[j]));
                ans[i] = ans[i].divide(a[i][i]);
            }

            for (int i = 0; i < n; i++) out.println(ans[i]);
            out.println();

            /*
            for (int i = 0; i < n; i++) {
                Fraction test = new Fraction(BigInteger.ZERO, BigInteger.ONE);
                for (int j = 0; j < n; j++) {
                    test = test.add(aa[i][j].multiply(ans[j]));
                    // out.println(test);
                }
                // out.println(bb[i]);
                out.println(test.subtract(bb[i]) + " ");
            }
            out.println();
            out.println();
            */

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
