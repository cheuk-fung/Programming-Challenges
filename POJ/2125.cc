/*
 *  SRC: POJ 2125
 * PROB: Destroying The Graph
 * ALGO: Dinic
 * DATE: Jul 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXV = 209;
const int MAXE = 50000;
const int INF = 0x3f3f3f3f;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v;
    int c, f;
    Edge *next;
    Edge *rev;
};
Edge e_buf[MAXE];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
Edge *e_tail = e_buf;

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
    memset(lev, 0xff, sizeof lev);
    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;
    while (head != tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next) {
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
        }
    }
    return lev[dest] != -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    for (Edge *&e = e_work[u]; e; e = e->next) {
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) return res;
        }
    }

    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        memcpy(e_work, e_head, sizeof e_head);
        int tmp = dfs(orig, INF);
        if (!tmp) break;
        res += tmp;
    }
    return res;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int w;
        scanf("%d", &w);
        add_edge(i + n + 1, dest, w);
    }
    for (int i = 0; i < n; i++) {
        int w;
        scanf("%d", &w);
        add_edge(orig, i + 1, w);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v + n, INF);
    }
    printf("%d\n", dinic());

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (lev[i] == -1) {
            cnt++;
        }
    }
    for (int i = n + 1; i <= n << 1; i++) {
        if (lev[i] != -1) {
            cnt++;
        }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) {
        if (lev[i] == -1) {
            printf("%d -\n", i);
        }
    }
    for (int i = n + 1; i <= n << 1; i++) {
        if (lev[i] != -1) {
            printf("%d +\n", i - n);
        }
    }

    return 0;
}

