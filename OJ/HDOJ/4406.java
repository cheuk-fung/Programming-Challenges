/*
 *  SRC: HDOJ 4406
 * PROB: GPA
 * ALGO: MCMF
 * DATE: Sep 23, 2012
 * COMP: jdk6
 * Created by Leewings Ng
 */

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class Main {
    private static final int NEGINF = 0xc0c0c0c0;

    private Edge[] ehead;
    private Rnode[] road;

    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        Scanner cin = new Scanner(System.in);
        while (true) {
            int n = cin.nextInt();
            int k = cin.nextInt();
            int m = cin.nextInt();
            if (n == 0 && k == 0 && m == 0) break;

            int nodecnt = n + m + 2;
            ehead = new Edge[nodecnt];
            road = new Rnode[nodecnt];
            int s = nodecnt - 1, t = s - 1;

            int[] credits = new int[m];
            int[] score = new int[m];

            int totW = 0;
            for (int i = 0; i < m; i++) {
                credits[i] = cin.nextInt();
                totW += credits[i];
            }

            for (int i = 0; i < m; i++) {
                score[i] = cin.nextInt();
                int now = score[i];
                if (now < 60) {
                    addedge(s, i, 60 - now, NEGINF);
                    now = 60;
                }

                for (int j = now + 1; j <= 100; j++) {
                    addedge(s, i, 1, (gradePoint(j - 1) - gradePoint(j)) * credits[i]);
                }
            }

            for (int i = 0; i < n; i++) {
                addedge(i + m, t, k, 0);
                for (int j = 0; j < m; j++) {
                    if (cin.nextInt() == 1) {
                        addedge(j, i + m, k, 0);
                    }
                }
            }

            mcmf(nodecnt, s, t);
            for (Edge e = ehead[s]; e != null; e = e.next) {
                score[e.v] += e.f;
            }

            long totPW = 0;
            boolean ok = true;
            for (int i = 0; i < m; i++) {
                totPW += gradePoint(score[i]) * credits[i];
                if (score[i] < 60) ok = false;
            }

            if (!ok) {
                System.out.println("0.000000");
            } else {
                double GPA = totPW / 1600.0 / totW;
                String str = String.format("%.6f", GPA);
                System.out.println(str);
            }
        }
    }

    private long gradePoint(int x)
    {
        return 4 * 1600 - 3 * (100 - x) * (100 - x);
    }

    private void addedge(int u, int v, int c, long cpf)
    {
        ehead[u] = new Edge(v, c, 0, cpf, ehead[u]);
        ehead[v] = new Edge(u, 0, 0, -cpf, ehead[v]);
        ehead[u].rev = ehead[v];
        ehead[v].rev = ehead[u];
    }

    private void mcmf(int n, int s, int t)
    {
        while (spfa(n, s, t)) flow(t);
    }

    private boolean spfa(int n, int s, int t)
    {
        long[] dist = new long[n];
        boolean[] inqueue = new boolean[n];
        Queue<Integer> Q = new LinkedList<Integer>();
        dist[s] = 0;
        Q.offer(s);
        inqueue[s] = true;
        road[s] = new Rnode(null, null);
        while (!Q.isEmpty()) {
            int u = Q.poll();
            inqueue[u] = false;
            for (Edge e = ehead[u]; e != null; e = e.next) {
                if (e.f < e.c && dist[u] + e.cpf < dist[e.v]) {
                    dist[e.v] = dist[u] + e.cpf;
                    road[e.v] = new Rnode(road[u], e);
                    if (!inqueue[e.v]) {
                        Q.offer(e.v);
                        inqueue[e.v] = true;
                    }
                }
            }
        }
        return dist[t] < 0;
    }

    private void flow(int t)
    {
        int f = Integer.MAX_VALUE;
        for (Rnode r = road[t]; r.next != null; r = r.next) {
            f = Math.min(f, r.which.c - r.which.f);
        }

        for (Rnode r = road[t]; r.next != null; r = r.next) {
            r.which.f += f;
            r.which.rev.f = -r.which.f;
        }
    }

    private class Edge {
        int v, c, f;
        long cpf;
        Edge next, rev;

        private Edge(int v, int c, int f, long cpf, Edge next)
        {
            this.v = v;
            this.c = c;
            this.f = f;
            this.cpf = cpf;
            this.next = next;
        }
    }

    private class Rnode {
        Rnode next;
        Edge which;

        private Rnode(Rnode next, Edge which)
        {
            this.next = next;
            this.which = which;
        }
    }
}
