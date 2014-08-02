/*
 *  SRC: HDOJ 4115
 * PROB: Eliminate the Conflict
 * ALGO: 2-SAT
 * DATE: Sep 26, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Stack;
import java.util.StringTokenizer;

class Main {
    ArrayList<ArrayList<Integer>> edge;
    private int timestampe;
    private int scccnt;
    private int[] dfn;
    private int[] low;
    private int[] sccid;
    private boolean[] instack;
    private Stack<Integer> S;

    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        MyReader in = new MyReader();

        int tasks = in.nextInt();
        for (int task = 1; task <= tasks; task++) {
            int n = in.nextInt();
            int m = in.nextInt();

            edge = new ArrayList<ArrayList<Integer>>();
            for (int i = 0; i < n * 6; i++) edge.add(new ArrayList<Integer>());
            for (int i = 0; i < n; i++) {
                int b = in.nextInt() - 1;
                int a = (b + 1) % 3;
                int c = (b - 1 + 3) % 3;
                edge.get(i * 6 + (a << 1 | 1)).add(i * 6 + (b << 1));
                edge.get(i * 6 + (b << 1 | 1)).add(i * 6 + (a << 1));
                edge.get(i * 6 + (c << 1)).add(i * 6 + (c << 1 | 1));

                for (int x = 0; x < 3; x++) {
                    a = (x + 1) % 3;
                    c = (x - 1 + 3) % 3;
                    edge.get(i * 6 + (x << 1)).add(i * 6 + (a << 1 | 1));
                    edge.get(i * 6 + (x << 1)).add(i * 6 + (c << 1 | 1));
                }
            }
            for (int i = 0; i < m; i++) {
                int a = in.nextInt() - 1;
                int b = in.nextInt() - 1;
                int k = in.nextInt();
                for (int x = 0; x < 3; x++) {
                    edge.get(a * 6 + (x << 1)).add(b * 6 + (x << 1 | k));
                    edge.get(b * 6 + (x << 1)).add(a * 6 + (x << 1 | k));
                }
            }

            System.out.println("Case #" + task + ": " + (sat(n * 6) ? "yes" : "no"));
        }
    }

    private boolean sat(int n)
    {
        tarjan(n);
        for (int i = 0; i < n; i += 2) {
            if (sccid[i] == sccid[i ^ 1]) {
                return false;
            }
        }
        return true;
    }

    private void tarjan(int n)
    {
        timestampe = scccnt = 0;
        dfn = new int[n];
        low = new int[n];
        sccid = new int[n];
        instack = new boolean[n];
        S = new Stack<Integer>();

        Arrays.fill(dfn, -1);
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                tarjanDFS(i);
            }
        }
    }

    private void tarjanDFS(int u)
    {
        S.add(u);
        instack[u] = true;
        dfn[u] = low[u] = timestampe++;

        for (int v : edge.get(u)) {
            if (dfn[v] == -1) {
                tarjanDFS(v);
                low[u] = Math.min(low[u], low[v]);
            } else if (instack[v]) {
                low[u] = Math.min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            int v;
            do {
                v = S.pop();
                instack[v] = false;
                sccid[v] = scccnt;
            } while (v != u);
            scccnt++;
        }
    }

    class MyReader {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in;

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
            while (in == null || !in.hasMoreTokens()) {
                try {
                    String line = br.readLine();
                    in = new StringTokenizer(line);
                } catch (Exception e) {
                    return false;
                }
            }
            return true;
        }

        int nextInt() { return Integer.parseInt(next()); }
    }
}
