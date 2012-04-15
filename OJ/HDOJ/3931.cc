/*
 *  SRC: HDOJ 3931
 * PROB: Cross the Fire
 * ALGO: Dinic
 * DATE: Apr 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

const int INF = 0x3f3f3f3f;
const int MAXV = 1010;
const int MAXE = 1000000;
const int orig = 0, dest = 1000;

struct Edge {
    int v;
    int c, f; // capa, flow
    Edge *next;
    Edge *rev; // revese edge
};
Edge e_buf[MAXE];
Edge *e_head[MAXV];
Edge *e_tail;

int que[MAXV], lev[MAXV];

inline void add_edge(int u, int v, int c)
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
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
    }

    return lev[dest] > -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    for (Edge *e = e_head[u]; e; e = e->next)
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) break;
        }

    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        int tmp = dfs(orig, INF);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

struct Circle {
    int x, y, r, p;
};
Circle c[300];

inline int sqr(int x) { return x * x; }

inline bool intersect(const Circle &a, const Circle &b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y) <= sqr(a.r + b.r);
}

int main()
{
    int l, w, n, p;
    while (~scanf("%d%d%d%d", &l, &w, &n, &p)) {
        memset(e_buf, 0, sizeof(e_buf));
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d", &c[i].x, &c[i].y, &c[i].r, &c[i].p);
            add_edge(i, i + n, c[i].p);
            if (c[i].y - c[i].r <= 0) {
                add_edge(orig, i, INF);
            }
            if (c[i].y + c[i].r >= w) {
                add_edge(i + n, dest, INF);
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (intersect(c[i], c[j])) {
                    add_edge(i + n, j, INF);
                    add_edge(j + n, i, INF);
                }
            }
        }

        int max_flow = dinic();
        if (max_flow > p) {
            puts("Our hero has been killed");
        } else {
            printf("%d\n", p - max_flow);
        }
    }

    return 0;
}

