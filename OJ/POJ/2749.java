/*
 *  SRC: POJ 2749
 * PROB: Building roads
 * ALGO: 2-SAT
 * DATE: Sep 24, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;

class Main {
    private Point[] pnt;
    private Point S1;
    private Point S2;
    private Point[] hate;
    private Point[] friend;
    private ArrayList<ArrayList<Integer>> edge;

    private int scccnt;
    private int timestampe;
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
            int a = cin.nextInt();
            int b = cin.nextInt();

            pnt = new Point[n];
            S1 = new Point(cin.nextInt(), cin.nextInt());
            S2 = new Point(cin.nextInt(), cin.nextInt());
            int minDistance = Integer.MAX_VALUE, maxDistance = 0;
            for (int i = 0; i < n; i++) {
                pnt[i] = new Point(cin.nextInt(), cin.nextInt());
                minDistance = Math.min(minDistance, Math.min(distance(pnt[i], S1), distance(pnt[i], S2)));
                maxDistance = Math.max(maxDistance, Math.max(distance(pnt[i], S1), distance(pnt[i], S2)));
            }

            hate = new Point[a];
            for (int i = 0; i < a; i++) {
                hate[i] = new Point(cin.nextInt() - 1, cin.nextInt() - 1);
            }

            friend = new Point[b];
            for (int i = 0; i < b; i++) {
                friend[i] = new Point(cin.nextInt() - 1, cin.nextInt() - 1);
            }

            int low = minDistance * 2, high = maxDistance * 2 + distance(S1, S2);
            while (low < high) {
                int mid = (low + high - 1) >> 1;
                if (check(mid)) high = mid;
                else low = mid + 1;
            }

            if (check(low)) {
                System.out.println(low);
            } else {
                System.out.println(-1);
            }
        }
    }

    private boolean check(int maxDistance)
    {
        edge = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < pnt.length << 1; i++) {
            edge.add(new ArrayList<Integer>());
        }

        for (Point p : hate) {
            edge.get(p.x << 1).add(p.y << 1 | 1);
            edge.get(p.x << 1 | 1).add(p.y << 1);
            edge.get(p.y << 1).add(p.x << 1 | 1);
            edge.get(p.y << 1 | 1).add(p.x << 1);
        }
        for (Point p : friend) {
            edge.get(p.x << 1).add(p.y << 1);
            edge.get(p.x << 1 | 1).add(p.y << 1 | 1);
            edge.get(p.y << 1).add(p.x << 1);
            edge.get(p.y << 1 | 1).add(p.x << 1 | 1);
        }
        for (int i = 0; i < pnt.length; i++) {
            for (int j = i + 1; j < pnt.length; j++) {
                boolean a = distance(pnt[i], S1) + distance(pnt[j], S1) > maxDistance;
                boolean b = distance(pnt[i], S2) + distance(pnt[j], S2) > maxDistance;
                boolean c = distance(pnt[i], S1) + distance(pnt[j], S2) + distance(S1, S2) > maxDistance;
                boolean d = distance(pnt[i], S2) + distance(pnt[j], S1) + distance(S1, S2) > maxDistance;
                if (a && b && c && d) return false;

                if (a) {
                    edge.get(i << 1).add(j << 1 | 1);
                    edge.get(j << 1).add(i << 1 | 1);
                }
                if (b) {
                    edge.get(i << 1 | 1).add(j << 1);
                    edge.get(j << 1 | 1).add(i << 1);
                }
                if (c) {
                    edge.get(i << 1).add(j << 1);
                    edge.get(j << 1 | 1).add(i << 1 | 1);
                }
                if (d) {
                    edge.get(i << 1 | 1).add(j << 1 | 1);
                    edge.get(j << 1).add(i << 1);
                }
            }
        }

        return sat();
    }

    private boolean sat()
    {
        tarjan();
        for (int i = 0; i < sccid.length; i += 2) {
            if (sccid[i] == sccid[i ^ 1]) {
                return false;
            }
        }

        return true;
    }

    private void tarjan()
    {
        scccnt = timestampe = 0;
        sccid = new int[edge.size()];
        dfn = new int[edge.size()];
        low = new int[edge.size()];
        instack = new boolean[edge.size()];
        S = new Stack<Integer>();

        Arrays.fill(dfn, -1);
        for (int i = 0; i < edge.size(); i++) {
            if (dfn[i] == -1) {
                tarjanDFS(i);
            }
        }
    }

    private void tarjanDFS(int u)
    {
        dfn[u] = low[u] = timestampe++;
        S.add(u);
        instack[u] = true;

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

    private int distance(Point u, Point v)
    {
        return Math.abs(u.x - v.x) + Math.abs(u.y - v.y);
    }

    private class Point {
        int x, y;

        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }
}
