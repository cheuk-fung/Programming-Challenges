import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    static MyReader in = new MyReader();

     throws IOException
    {

        return res;
    }

/*
    public static void main(String[] args) throws IOException
    {
        Main temp = new Main();
        System.out.println(temp.method());
    }
*/

    public void debug(Object...x)
    {
        System.out.println(Arrays.deepToString(x));
    }
}

class MyReader {
    private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    private static StringTokenizer in;

    public boolean hasNext() throws IOException
    {
        if (in == null || in.hasMoreTokens()) return true;
        String line = br.readLine();
        if (line == null) return false;
        in = new StringTokenizer(line);
        return true;
    }

    public String next() throws IOException
    {
        while (in == null || !in.hasMoreTokens())
            in = new StringTokenizer(br.readLine());
        return in.nextToken();
    }

    public int nextInt() throws IOException { return Integer.parseInt(next()); }
    public long nextLong() throws IOException { return Long.parseLong(next()); }
    public double nextDouble() throws IOException { return Double.parseDouble(next()); }
    public BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }
    public BigDecimal nextBigDecimal() throws IOException { return new BigDecimal(next()); }
}
