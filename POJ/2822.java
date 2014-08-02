/*
 *  SRC: POJ 2822
 * PROB: TN's Kingdom IV - Collapse
 * ALGO: Minimum Cut -> SSSP
 * DATE: Sep 24, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class Main {
    private static final double INF = 1e10;

    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        Scanner cin = new Scanner(System.in);

        int n = cin.nextInt();
        int m = cin.nextInt();

        ArrayList<Point> pnt = new ArrayList<Point>();
        for (int i = 0; i < n; i++) {
            pnt.add(new Point(cin.nextInt(), cin.nextInt()));
        }
        int s = pnt.indexOf(Collections.min(pnt));
        int t = pnt.indexOf(Collections.max(pnt));

        ArrayList<Arc>[] arc = new ArrayList[n];
        for (int i = 0; i < n; i++) arc[i] = new ArrayList<Arc>();

        int eid = 0;
        arc[s].add(new Arc(t, INF, eid++, Math.acos(-1)));
        arc[t].add(new Arc(s, INF, eid++, 0));
        for (int i = 0; i < m; i++) {
            int u = cin.nextInt();
            int v = cin.nextInt();
            double d = cin.nextDouble();
            arc[u].add(new Arc(v, d, eid++, angle(pnt.get(u), pnt.get(v))));
            arc[v].add(new Arc(u, d, eid++, angle(pnt.get(v), pnt.get(u))));
        }

        int[] next = new int[eid];
        for (int i = 0; i < n; i++) {
            Collections.sort(arc[i]);
            for (int j = 0; j < arc[i].size() - 1; j++) {
                next[arc[i].get(j).eid ^ 1] = arc[i].get(j + 1).eid;
            }
            next[arc[i].get(arc[i].size() - 1).eid ^ 1] = arc[i].get(0).eid;
        }

        int cid = 0;
        int[] col = new int[eid];
        Arrays.fill(col, -1);
        for (int i = 0; i < eid; i++) {
            if (col[i] == -1) {
                for (int x = i; col[x] == -1; x = next[x]) {
                    col[x] = cid;
                }
                cid++;
            }
        }

        ArrayList<Edge>[] edge = new ArrayList[cid];
        for (int i = 0; i < cid; i++) edge[i] = new ArrayList<Edge>();
        for (int i = 0; i < n; i++) {
            for (Arc a : arc[i]) {
                edge[col[a.eid]].add(new Edge(col[a.eid ^ 1], a.d));
            }
        }

        double r = spfa(edge, col[0], col[1]);
        System.out.printf("%.4f%n", r);
    }

    private double spfa(ArrayList<Edge>[] edge, int s, int t)
    {
        double[] dist = new double[edge.length];
        boolean[] inqueue = new boolean[edge.length];
        Arrays.fill(dist, INF);
        dist[s] = 0;

        Queue<Integer> Q = new LinkedList<Integer>();
        Q.add(s);
        while (!Q.isEmpty()) {
            int u = Q.poll();
            inqueue[u] = false;
            for (Edge e : edge[u]) {
                if (dist[u] + e.d < dist[e.v]) {
                    dist[e.v] = dist[u] + e.d;
                    if (!inqueue[e.v]) {
                        Q.add(e.v);
                        inqueue[e.v] = true;
                    }
                }
            }
        }

        return dist[t];
    }

    private double angle(Point u, Point v)
    {
        return Math.atan2(v.y - u.y, v.x - u.x);
    }

    private class Point implements Comparable<Point> {
        int x, y;

        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(Point o)
        {
            return x - o.x;
        }
    }

    private class Arc implements Comparable<Arc> {
        int v;
        double d;
        int eid;
        double agl;

        public Arc(int v, double d, int eid, double agl)
        {
            this.v = v;
            this.d = d;
            this.eid = eid;
            this.agl = agl;
        }

        @Override
        public int compareTo(Arc o)
        {
            if (agl > o.agl) return 1;
            if (agl < o.agl) return -1;
            return 0;
        }
    }

    private class Edge {
        int v;
        double d;

        public Edge(int v, double d)
        {
            this.v = v;
            this.d = d;
        }
    }
}
