import java.util.*;
import java.io.*;
import java.math.*;

public class D {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static final MyReader cin = new MyReader();
    static final int INF = 0x3f3f3f3f;

    class Edge {
        int u, v;

        Edge(int u, int v)
        {
            this.u = u;
            this.v = v;
        }
    }

    void solve() throws IOException
    {
        while (cin.hasNext()) {
            int n = cin.nextInt();
            Edge[] edges = new Edge[n];
            Vector<Integer>[] e = new Vector[n + 1];
            for (int i = 1; i <= n; i++) {
                e[i] = new Vector<Integer>();
            }

            int[] degree = new int[n + 1];
            for (int i = 1; i < n; i++) {
                int u = cin.nextInt();
                int v = cin.nextInt();
                edges[i] = new Edge(u, v);
                e[u].add(v);
                e[v].add(u);
                degree[u]++;
                degree[v]++;
            }

            int root = 1;
            for (int i = 2; i <= n; i++) {
                if (degree[i] > 2) {
                    root = i;
                    break;
                }
            }

            int idCnt = 0;
            int[] dist = new int[n + 1];
            int[] id = new int[n + 1];
            int[] headVer = new int[n + 1];
            for (int u : e[root]) {
                dist[u] = 1;
                id[u] = ++idCnt;
                headVer[u] = u;
                for (int last = root; degree[u] != 1; ) {
                    for (int v : e[u]) {
                        if (v == last) continue;

                        dist[v] = dist[u] + 1;
                        id[v] = ++idCnt;
                        headVer[v] = headVer[u];
                        last = u;
                        u = v;
                        break;
                    }
                }
            }

            int[] farther = new int[n];
            for (int i = 1; i < n; i++) {
                farther[i] = dist[edges[i].u] > dist[edges[i].v] ? edges[i].u : edges[i].v;
            }

            BIT bit = new BIT(n + 1);
            int m = cin.nextInt();
            while (m-- > 0) {
                int type = cin.nextInt();
                switch (type) {
                    case 1:
                        bit.update(id[farther[cin.nextInt()]], -1);
                        break;
                    case 2:
                        bit.update(id[farther[cin.nextInt()]], 1);
                        break;
                    case 3:
                        int u = cin.nextInt();
                        int v = cin.nextInt();
                        if (headVer[u] == headVer[v]) {
                            if (bit.sum(id[u]) - bit.sum(id[v]) != 0) {
                                System.out.println("-1");
                            } else {
                                System.out.println(Math.abs(dist[u] - dist[v]));
                            }
                        } else {
                            if (bit.sum(id[u]) - bit.sum(id[headVer[u]] - 1) + bit.sum(id[v]) - bit.sum(id[headVer[v]] - 1) != 0) {
                                System.out.println("-1");
                            } else {
                                System.out.println(dist[u] + dist[v]);
                            }
                        }
                }
            }
        }
    }
}

class BIT {
    private int bound;
    private int[] c;

    private int lowbit(int x) { return x & -x; }

    BIT(int bound)
    {
        this.bound = bound;
        c = new int[bound + 1];
    }

    void update(int x, int val)
    {
        for ( ; x <= bound; c[x] += val, x += lowbit(x))
            ;
    }

    int sum(int x)
    {
        if (x < 0) return 0;

        int res = 0;
        for ( ; x > 0; res += c[x], x -= lowbit(x))
            ;
        return res;
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
    long nextLong() throws IOException { return Long.parseLong(next()); }
    double nextDouble() throws IOException { return Double.parseDouble(next()); }
    BigInteger nextBigInteger() throws IOException { return new BigInteger(next()); }
    BigDecimal nextBigDecimal() throws IOException { return new BigDecimal(next()); }
}
