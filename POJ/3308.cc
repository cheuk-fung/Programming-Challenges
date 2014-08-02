/*
 *  SRC: POJ 3308
 * PROB: Paratroopers
 * ALGO: Dinic
 * DATE: Jul 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const double INF = 1e10;
const double eps = 1e-8;
const int MAXV = 111;
const int MAXE = 2012;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v;
    double c, f;
    Edge *next, *rev;
};
Edge e_buf[MAXE];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
Edge *e_tail;

int que[MAXV], lev[MAXV];

inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline double dmin(double x, double y) { return ls(x, y) ? x : y; }

inline void add_edge(int u, int v, double c)
{
    *e_tail = (Edge){v, c, 0, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof(lev));

    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;

    while (head != tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next) 
            if (lev[e->v] == -1 && ls(e->f, e->c)) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
    }
    return lev[dest] > -1;
}

double dfs(int u, double f)
{
    if (u == dest) return f;

    double res = 0;
    for (Edge *e = e_work[u]; e; e = e->next)
        if (lev[e->v] == lev[u] + 1 && ls(e->f, e->c)) {
            double tmp = dfs(e->v, dmin(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (eq(res, f)) break;
        }
    return res;
}

double dinic()
{
    double res = 0;
    while (bfs()) {
        memcpy(e_work, e_head, sizeof(e_head));
        double tmp = dfs(orig, INF);
        if (gr(tmp, 0)) res += tmp;
        else break;
    }
    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        int m, n, l;
        scanf("%d%d%d", &m, &n, &l);

        for (int i = 1; i <= m; i++) {
            double r;
            scanf("%lf", &r);
            add_edge(orig, i, log(r));
        }
        for (int i = 1; i <= n; i++) {
            double c;
            scanf("%lf", &c);
            add_edge(i + m, dest, log(c));
        }
        for (int i = 0; i < l; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v + m, INF);
        }

        printf("%.4f\n", exp(dinic()));
    }

    return 0;
}
