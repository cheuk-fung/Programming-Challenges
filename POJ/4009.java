/*
 *  SRC: POJ 4009
 * PROB: Porcelain Exhibitions
 * ALGO: Network flow
 * DATE: Sep 28, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

class Main {
    private static final long LLINF = 0x3f3f3f3f3f3f3f3fl;

    public static void main(String[] args)
    {
        new Main().run();
    }

    private Arc[] archead;
    private Arc[] arcwork;
    private int[] lev;

    private void run()
    {
        MyReader in = new MyReader();
        while (true) {
            int n = in.nextInt();
            int m = in.nextInt();
            int minK = in.nextInt();
            int maxK = in.nextInt();
            int p = in.nextInt();
            if (n == 0 && m == 0 && minK == 0 && maxK == 0 && p == 0) break;

            Point[] points = new Point[n];
            for (int i = 0; i < n; i++) points[i] = new Point(in.nextInt(), in.nextInt());

            Edge[] edges = new Edge[m << 1];
            ArrayList<ArrayList<Node>> nodeList = new ArrayList<ArrayList<Node>>();
            for (int i = 0; i < n; i++) nodeList.add(new ArrayList<Node>());

            int eid = 0;
            for (int i = 0; i < m; i++) {
                int u = in.nextInt();
                int v = in.nextInt();
                int w = in.nextInt();
                edges[eid] = new Edge(u, v, w);
                nodeList.get(u).add(new Node(v, w, eid++, calcAngle(points[u], points[v])));
                edges[eid] = new Edge(v, u, w);
                nodeList.get(v).add(new Node(u, w, eid++, calcAngle(points[v], points[u])));
            }

            int[] next = new int[eid];
            for (int i = 0; i < n; i++) {
                Collections.sort(nodeList.get(i));
                for (int j = 0; j < nodeList.get(i).size() - 1; j++) {
                    next[nodeList.get(i).get(j).eid ^ 1] = nodeList.get(i).get(j + 1).eid;
                }
                next[nodeList.get(i).get(nodeList.get(i).size() - 1).eid ^ 1] = nodeList.get(i).get(0).eid;
            }

            int cid = 0;
            int[] color = new int[eid];
            Arrays.fill(color, -1);
            ArrayList<Long> porcelains = new ArrayList<Long>();
            for (int i = 0; i < eid; i++) {
                if (color[i] == -1) {
                    long now = 0;
                    for (int x = i; color[x] == -1; x = next[x]) {
                        color[x] = cid;
                        now += calcArea(points[edges[x].v], points[edges[x].u]);
                    }
                    porcelains.add(now * p / 2);
                    cid++;
                }
            }

            int s = cid, t = s + 1;
            int vs = t + 1, vt = vs + 1;
            int nodeCount = vt + 1;
            long sum = 0;
            archead = new Arc[nodeCount];
            for (int i = 0; i < cid; i++) {
                if (porcelains.get(i) < 0) continue;
                addEdge(s, i, porcelains.get(i));
                addEdge(i, t, maxK - minK);
                addEdge(i, vt, minK);
                addEdge(vs, t, minK);
                sum += minK;
            }
            for (int i = 0; i < eid; i++) {
                addEdge(color[i], color[i ^ 1], edges[i].w);
            }
            addEdge(t, s, LLINF);

            long r = dinic(nodeCount, vs, vt);
            if (r != sum) {
                System.out.println(-1);
            } else {
                r = dinic(nodeCount, s, t);
                System.out.println(r);
            }
        }
    }

    private double calcAngle(Point u, Point v)
    {
        return Math.atan2(v.y - u.y, v.x - u.x);
    }

    private long calcArea(Point u, Point v)
    {
        return (long)u.x * v.y - (long)u.y * v.x;
    }

    private void addEdge(int u, int v, long c)
    {
        archead[u] = new Arc(v, c, 0, archead[u]);
        archead[v] = new Arc(u, 0, 0, archead[v]);
        archead[u].rev = archead[v];
        archead[v].rev = archead[u];
    }

    private long dinic(int n, int s, int t)
    {
        long r = 0;
        while (bfs(n, s, t)) {
            arcwork = archead.clone();
            long tmp = dfs(s, t, LLINF);
            if (tmp == 0) break;
            r += tmp;
        }
        return r;
    }

    private boolean bfs(int n, int s, int t)
    {
        lev = new int[n];
        Arrays.fill(lev, -1);
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(s);
        lev[s] = 0;
        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (Arc arc = archead[u]; arc != null; arc = arc.next) {
                if (lev[arc.v] == -1 && arc.f < arc.c) {
                    lev[arc.v]= lev[u] + 1;
                    queue.add(arc.v);
                }

            }
        }
        return lev[t] != -1;
    }

    private long dfs(int u, int t, long f)
    {
        if (u == t) return f;

        long r = 0;
        for ( ; arcwork[u] != null; arcwork[u] = arcwork[u].next) {
            Arc arc = arcwork[u];
            if (lev[arc.v] == lev[u] + 1 && arc.f < arc.c) {
                long ret = dfs(arc.v, t, Math.min(f - r, arc.c - arc.f));
                r += ret;
                arc.f += ret;
                arc.rev.f = -arc.f;
                if (r == f) break;
            }
        }
        return r;
    }

    class Point {
        int x, y;

        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    class Edge {
        int u, v, w;

        public Edge(int u, int v, int w)
        {
            this.u = u;
            this.v = v;
            this.w = w;
        }
    }

    class Node implements Comparable<Node> {
        int v, w, eid;
        double angle;

        public Node(int v, int w, int eid, double angle)
        {
            this.v = v;
            this.w = w;
            this.eid = eid;
            this.angle = angle;
        }

        @Override
        public int compareTo(Node o)
        {
            if (angle > o.angle) return 1;
            if (angle < o.angle) return -1;
            return 0;
        }
    }

    class Arc {
        int v;
        long c, f;
        Arc next, rev;

        public Arc(int v, long c, long f, Arc next)
        {
            this.v = v;
            this.c = c;
            this.f = f;
            this.next = next;
        }
    }

    class MyReader {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer token;

        boolean hasNext()
        {
            while (token == null || !token.hasMoreTokens()) {
                try {
                    token = new StringTokenizer(br.readLine());
                } catch (Exception e) {
                    return false;
                }
            }
            return true;
        }

        String next()
        {
            if (hasNext()) return token.nextToken();
            return null;
        }

        int nextInt() { return Integer.parseInt(next()); }
    }
}
