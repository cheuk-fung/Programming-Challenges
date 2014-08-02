/*
 *  SRC: POJ 3905
 * PROB: Perfect Election
 * ALGO: 2-SAT
 * DATE: Sep 26, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Stack;
import java.util.StringTokenizer;

class Main {
    private ArrayList<ArrayList<Integer>> edge;
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
        PrintWriter out = new PrintWriter(System.out);

        while (true) {
            try {
                int n = in.nextInt();
                int m = in.nextInt();

                edge = new ArrayList<ArrayList<Integer>>();
                for (int i = 0; i < n << 1; i++) edge.add(new ArrayList<Integer>());
                for (int i = 0; i < m; i++) {
                    String a = in.next();
                    String b = in.next();
                    int u = (a.charAt(0) == '+' ? 1 : -1) * Integer.parseInt(a.substring(1));
                    int v = (b.charAt(0) == '+' ? 1 : -1) * Integer.parseInt(b.substring(1));
                    if (u > 0 && v > 0) {
                        u--;
                        v--;
                        edge.get(u << 1 | 1).add(v << 1);
                        edge.get(v << 1 | 1).add(u << 1);
                    } else if (u < 0 && v < 0) {
                        u = -u - 1;
                        v = -v - 1;
                        edge.get(u << 1).add(v << 1 | 1);
                        edge.get(v << 1).add(u << 1 | 1);
                    } else if (u > 0 && v < 0) {
                        u--;
                        v = -v - 1;
                        edge.get(u << 1 | 1).add(v << 1 | 1);
                        edge.get(v << 1).add(u << 1);
                    } else {
                        u = -u - 1;
                        v--;
                        edge.get(u << 1).add(v << 1);
                        edge.get(v << 1 | 1).add(u << 1 | 1);
                    }
                }

                out.println(sat(n << 1) ? "1" : "0");
            } catch (Exception e) {
                break;
            }
        }
        out.flush();
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
