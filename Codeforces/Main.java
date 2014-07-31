import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    static final MyReader in = new MyReader();
    static final PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args)
    {
        new Main().run();
    }

    void run()
    {

        out.flush();
    }

    static void debug(Object...o)
    {
        System.err.println(Arrays.deepToString(o));
    }
}

class MyReader {
    static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer in;

    String next()
    {
        while (in == null || !in.hasMoreTokens()) {
            try {
                in = new StringTokenizer(br.readLine());
            } catch (Exception e) {
                return null;
            }
        }
        return in.nextToken();
    }

    boolean hasNext()
    {
        if (in == null || in.hasMoreTokens()) return true;
        try {
            String line = br.readLine();
            in = new StringTokenizer(line);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    int nextInt() { return Integer.parseInt(next()); }
    long nextLong() { return Long.parseLong(next()); }
    double nextDouble() { return Double.parseDouble(next()); }
    BigInteger nextBigInteger() { return new BigInteger(next()); }
    BigDecimal nextBigDecimal() { return new BigDecimal(next()); }
}

// Usage: Arrays.sort(test, new MyComparator());
class MyComparator implements Comparator<Main> {
    public int compare(Main a, Main b)
    {
        // return:
        //        1: a > b
        //        0: a = b
        //       -1: a < b
        return 0;
    }
}

