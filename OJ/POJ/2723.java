/*
 *  SRC: POJ 2723
 * PROB: Get Luffy Out
 * ALGO: 2-SAT
 * DATE: Sep 25, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;

class Main {
    private int[] index;
    private Pair[] doors;

    private int timestampe;
    private int scccnt;
    private ArrayList<ArrayList<Integer>> edge;
    private int[] sccid;
    private int[] dfn;
    private int[] low;
    private boolean[] instack;
    private Stack<Integer> S;

    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            int n = cin.nextInt();
            int m = cin.nextInt();
            if (n == 0 && m == 0) break;

            index = new int[n << 1];
            for (int i = 0; i < n; i++) {
                index[cin.nextInt()] = i << 1;
                index[cin.nextInt()] = i << 1 | 1;
            }

            doors = new Pair[m];
            for (int i = 0; i < m; i++) {
                doors[i] = new Pair(cin.nextInt(), cin.nextInt());
            }

            int low = 0, high = m;
            while (low < high) {
                int mid = (low + high + 1) >> 1;
                if (check(mid)) low = mid;
                else high = mid - 1;
            }
            System.out.println(low);
        }
    }

    private boolean check(int maxDoors)
    {
        edge = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < index.length; i++) edge.add(new ArrayList<Integer>());
        for (int i = 0; i < maxDoors; i++) {
            edge.get(index[doors[i].first] ^ 1).add(index[doors[i].second]);
            edge.get(index[doors[i].second] ^ 1).add(index[doors[i].first]);
        }
        return sat();
    }

    private boolean sat()
    {
        tarjan();
        for (int i = 0; i < index.length; i += 2) {
            if (sccid[i] == sccid[i ^ 1]) {
                return false;
            }
        }
        return true;
    }

    private void tarjan()
    {
        timestampe = scccnt = 0;
        sccid = new int[index.length];
        dfn = new int[index.length];
        low = new int[index.length];
        instack = new boolean[index.length];
        S = new Stack<Integer>();

        Arrays.fill(dfn, -1);
        for (int i = 0; i < index.length; i++) {
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

    class Pair {
        int first, second;

        Pair(int first, int second)
        {
            this.first = first;
            this.second = second;
        }
    }
}
