import java.io.*;
import java.util.*;
import java.math.*;

public class E {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static MyReader in = new MyReader();
    static PrintWriter out = new PrintWriter(System.out);

    void solve() throws IOException
    {
        int n = in.nextInt(),
            m = in.nextInt(),
            c = in.nextInt();

        int[] x = new int[n];
        long[] p = new long[n - 1];
        for (int i = 0; i < n; i++) x[i] = in.nextInt();
        for (int i = 0; i < n - 1; i++) p[i] = in.nextInt();

        SegTree st = new SegTree(n);
        st.build(0, n);
        for (int i = 0; i < n - 1; i++)
            st.insert(i, i + 1, (x[i + 1] - x[i]) * 50 - c * p[i]);

        long ans = 0;
        while (m-- > 0) {
            int a = in.nextInt(),
                b = in.nextInt();
            ans += st.query(a, b);
        }
        out.println(ans / 100.0);

        out.flush();
    }
}

class Tnode {
    int a, b;
    long maxL, maxR, sum, best;

    Tnode(int _a, int _b)
    {
        a = _a;
        b = _b;
    }
}

class Result {
    long maxL, maxR, sum, best;
}

class SegTree {
    static final int INF = 0x3f3f3f3f;

    Tnode[] node;
    Result[] res;

    SegTree(int size)
    {
        size *= 4;
        node = new Tnode[size];
        res = new Result[size];
    }

    void build(int a, int b) { build(a, b, 1); }
    void insert(int c, int d, long v) { insert(c, d, v, 1); };
    long query(int c, int d)
    {
        query(c - 1, d - 1, 1);
        return res[1].best;
    }

    void build(int a, int b, int idx) {
        node[idx] = new Tnode(a, b);
        res[idx] = new Result();
        if (a + 1 < b) {
            build(a, (a + b) / 2, idx * 2);
            build((a + b) / 2, b, idx * 2 + 1);
        }
    }

    void insert(int c, int d, long v, int idx)
    {
        if (c <= node[idx].a && node[idx].b <= d) {
            node[idx].maxL = node[idx].maxR = node[idx].sum = v;
            node[idx].best = Math.max(0, v);
            return ;
        }

        if (c < (node[idx].a + node[idx].b) / 2) insert(c, d, v, idx * 2);
        if (d > (node[idx].a + node[idx].b) / 2) insert(c, d, v, idx * 2 + 1);

        node[idx].maxL = Math.max(node[idx * 2].maxL, node[idx * 2].sum + node[idx * 2 + 1].maxL);
        node[idx].maxR = Math.max(node[idx * 2].maxR + node[idx * 2 + 1].sum, node[idx * 2 + 1].maxR);
        node[idx].sum  = node[idx * 2].sum + node[idx * 2 + 1].sum;
        node[idx].best = Math.max(Math.max(node[idx * 2].best, node[idx * 2 + 1].best), node[idx * 2].maxR + node[idx * 2 + 1].maxL);
    }

    void query(int c, int d, int idx)
    {
        if (c >= node[idx].b || d <= node[idx].a) {
            res[idx].maxL = res[idx].maxR = res[idx].sum = res[idx].best = 0;
            return ;
        }
        if (c <= node[idx].a && node[idx].b <= d) {
            res[idx].maxL = node[idx].maxL;
            res[idx].maxR = node[idx].maxR;
            res[idx].sum  = node[idx].sum;
            res[idx].best = node[idx].best;
            return ;
        }

        query(c, d, idx * 2);
        query(c, d, idx * 2 + 1);

        res[idx].maxL = Math.max(res[idx * 2].maxL, res[idx * 2].sum + res[idx * 2 + 1].maxL);
        res[idx].maxR = Math.max(res[idx * 2].maxR + res[idx * 2 + 1].sum, res[idx * 2 + 1].maxR);
        res[idx].sum  = res[idx * 2].sum + res[idx * 2 + 1].sum;
        res[idx].best = Math.max(Math.max(res[idx * 2].best, res[idx * 2 + 1].best), res[idx * 2].maxR + res[idx * 2 + 1].maxL);
    }
}

class MyReader {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
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
    long nextLong() throws IOException { return Long.parseLong(next()); }
    double nextDouble() throws IOException { return Double.parseDouble(next()); }
    BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }
    BigDecimal nextBigDecimal() throws IOException { return new BigDecimal(next()); }
}

