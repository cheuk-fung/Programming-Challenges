/*
 *  SRC: HDOJ 4318
 * PROB: Power transmission
 * ALGO: SSSP
 * DATE: Jul 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 50010;
const double DINF = 1e10;
const double eps = 1e-8;

inline bool gr(double x, double y) { return x - eps > y; }
inline bool ls(double x, double y) { return x + eps < y; }

struct Edge {
    int v;
    int b;
    double reduction, rest;
    Edge *next;

    bool operator <(const Edge &o) const
    {
        return gr(reduction, o.reduction);
    }
};
Edge e_buf[MAXN * 110];
Edge *e_head[MAXN];
Edge *e_tail;

double dist[MAXN];

inline void add_edge(int u, int v, int b)
{
    e_tail->v = v;
    e_tail->b = b;
    e_tail->next = e_head[u];
    e_head[u] = e_tail++;
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        memset(e_head, 0, sizeof e_head);
        e_tail = e_buf;

        for (int i = 1; i <= n; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                int a, b;
                scanf("%d%d", &a, &b);
                add_edge(i, a, b);
            }
        }

        int s, t;
        double m;
        scanf("%d%d%lf", &s, &t, &m);
        priority_queue<Edge> que;
        que.push((Edge){s, 0, 0, m});
        fill(dist, dist + n + 1, DINF);
        dist[s] = 0;
        while (!que.empty()) {
            Edge u = que.top();
            que.pop();
            if (gr(u.reduction, dist[u.v])) continue;
            for (Edge *e = e_head[u.v]; e; e = e->next) {
                double d = u.reduction + u.rest * e->b / 100;
                if (ls(d, dist[e->v])) {
                    dist[e->v] = d;
                    que.push((Edge){e->v, 0, d, m - d});
                }
            }
        }

        printf("%.2f\n", dist[t]);
    }

    return 0;
}

