/*
 *  SRC: POJ 3155
 * PROB: Hard Life
 * ALGO: Maximum Density Subgraph
 * DATE: Jul 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAXV = 110;
const int MAXE = 1010;
const double DINF = 1e10;
const double eps = 1e-8;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v;
    double c, f;

    Edge *next;
    Edge *rev;
};
Edge e_buf[MAXE << 3];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
Edge *e_tail;

int que[MAXV], lev[MAXV];

inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }

inline void add_edge(int u, int v, double c)
{
    assert(c >= 0);

    *e_tail = (Edge){v, c, 0, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof lev);

    int *head = que, *tail = que;
    lev[orig] = 0;
    *tail++ = orig;
    while (head != tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next) {
            if (lev[e->v] == -1 && ls(e->f, e->c)) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
        }
    }
    return lev[dest] != -1;
}

double dfs(int u, double f)
{
    if (u == dest) return f;

    double res = 0;
    for (Edge *&e = e_work[u]; e; e = e->next) {
        if (lev[e->v] == lev[u] + 1 && ls(e->f, e->c)) {
            double tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (eq(res, f)) return res;
        }
    }
    return res;
}

double dinic()
{
    double r = 0;
    while (bfs()) {
        memcpy(e_work, e_head, sizeof e_head);
        double f = dfs(orig, DINF);
        if (eq(f, 0)) break;
        r += f;
    }
    return r;
}

int n, m;
int maxdeg, deg[MAXV];
struct PEdge { int x, y; };
PEdge pe[MAXE];

bool check(double x)
{
    memset(e_head, 0, sizeof e_head);
    e_tail = e_buf;

    for (int i = 1; i <= n; i++) {
        add_edge(orig, i, maxdeg);
        add_edge(i, dest, maxdeg + 2 * x - deg[i]);
    }
    for (int i = 0; i < m; i++) {
        add_edge(pe[i].x, pe[i].y, 1);
        add_edge(pe[i].y, pe[i].x, 1);
    }

    double r = dinic();
    // double h = (maxdeg * n - r) / 2;
    return !eq(maxdeg * n, r);
}

int main()
{
    while (~scanf("%d%d", &n, &m)) {
        if (m == 0) {
            puts("1");
            puts("1");
            continue;
        }

        memset(deg, 0, sizeof deg);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &pe[i].x, &pe[i].y);
            deg[pe[i].x]++;
            deg[pe[i].y]++;
        }
        maxdeg = *max_element(deg + 1, deg + n + 1);

        double l = 1.0 / n, r = m, mingap = 1.0 / (n * (n - 1));
        while (!ls(r - l, mingap)) {
            double mid = (l + r) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }

        check(l);
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (lev[i] != -1) cnt++;
        }
        printf("%d\n", cnt);
        for (int i = 1; i <= n; i++) {
            if (lev[i] != -1) {
                printf("%d\n", i);
            }
        }
    }

    return 0;
}

