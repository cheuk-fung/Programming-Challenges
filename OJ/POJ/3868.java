/*
 *  SRC: POJ 3868
 * PROB: Garbling Game
 * ALGO: Math
 * DATE: Jul 10, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static final MyReader in = new MyReader();
    static final PrintWriter out = new PrintWriter(System.out);

    void solve() throws IOException
    {
        int r = in.nextInt();
        int c = in.nextInt();
        BigInteger n = in.nextBigInteger();

        int loop = (r - 1) * (c - 1);
        String[] change = new String[r - 1];
        for (int i = 0; i < r - 1; i++)
                change[i] = in.next();

        Matrix result = new Matrix(change, n.mod(BigInteger.valueOf(loop)).intValue());
        Matrix power = new Matrix(change, loop);
        BigInteger cnt = n.divide(BigInteger.valueOf(loop));
        while (!cnt.equals(BigInteger.ZERO)) {
            if (cnt.mod(BigInteger.valueOf(2)).equals(BigInteger.ONE)) {
                result = power.multiply(result);
            }
            power = power.multiply(power);
            cnt = cnt.divide(BigInteger.valueOf(2));
        }

        for (int i = 0; i < result.cnt.length; i++)
            out.println(result.cnt[i]);
        out.flush();
    }
}

class Matrix {
    int[] cnt;
    int[] perm;
    int[][] mat;

    Matrix(int n)
    {
        cnt = new int[n];
        perm = new int[n];
    }

    Matrix(String[] change, int loop)
    {
        int r = change.length + 1;
        int c = change[0].length() + 1;
        cnt = new int[r * c];
        perm = new int[r * c];
        mat = new int[r][c];
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                mat[i][j] = i * c + j;

        for (int i = 0; i < r - 1; i++)
            for (int j = 0; j < c - 1; j++) {
                if (loop-- == 0) return ;

                cnt[mat[i][j]]++;
                switch (change[i].charAt(j)) {
                    case 'L': rotateLeft(i, j); break;
                    case 'R': rotateRight(i, j);
                }
            }

        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                perm[mat[i][j]] = i * c + j;
    }

    void rotateLeft(int x, int y)
    {
        int t = mat[x][y];
        mat[x][y] = mat[x][y + 1];
        mat[x][y + 1] = mat[x + 1][y + 1];
        mat[x + 1][y + 1] = mat[x + 1][y];
        mat[x + 1][y] = t;
    }

    void rotateRight(int x, int y)
    {
        int t = mat[x][y];
        mat[x][y] = mat[x + 1][y];
        mat[x + 1][y] = mat[x + 1][y + 1];
        mat[x + 1][y + 1] = mat[x][y + 1];
        mat[x][y + 1] = t;
    }

    Matrix multiply(Matrix o)
    {
        int n = perm.length;
        Matrix result = new Matrix(n);;
        for (int i = 0; i < n; i++) {
            result.cnt[i] = (cnt[i] + o.cnt[perm[i]]) % 100000;
            result.perm[i] = o.perm[perm[i]];
        }
        return result;
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
    BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }
}
