/*
 *  SRC: POJ 2488
 * PROB: A Knight's Journey
 * ALGO: DFS
 * DATE: Mar 07, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static final MyReader in = new MyReader();
    static final PrintWriter out = new PrintWriter(System.out);

    int p, q;
    int[][] dir = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1} };
    boolean[][] vis;
    String route;

    boolean dfs(int x, int y, int cnt)
    {
        vis[x][y] = true;
        if (cnt == p * q) return true;
        for (int i = 0; i < 8; i++) {
            int xx = x + dir[i][0];
            int yy = y + dir[i][1];
            if (xx < 0 || xx >= q) continue;
            if (yy < 0 || yy >= p) continue;
            if (vis[xx][yy]) continue;

            String currRoute = route;
            route += (char)('A' + xx) + Integer.toString(yy + 1);
            if (dfs(xx, yy, cnt + 1))
                return true;
            route = currRoute;
        }
        vis[x][y] = false;
        return false;
    }

    void solve() throws IOException
    {
        int n = in.nextInt();
        for (int task = 1; task <= n; task++) {
            p = in.nextInt();
            q = in.nextInt();
            route = "A1";
            vis = new boolean[q][p];
            out.println("Scenario #" + task + ":");
            out.println(dfs(0, 0, 1) ? route : "impossible");
            out.println();
        }

        out.flush();
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

    int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }

    long nextLong() throws IOException
    {
        return Long.parseLong(next());
    }

    double nextDouble() throws IOException
    {
        return Double.parseDouble(next());
    }

    BigInteger nextBigInteger() throws IOException
    {
        return new BigInteger(next());
    }

    BigDecimal nextBigDecimal() throws IOException
    {
        return new BigDecimal(next());
    }
}
