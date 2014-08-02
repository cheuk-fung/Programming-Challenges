/*
 *  SRC: HDOJ 4289
 * PROB: Control
 * ALGO: Minimum cut
 * DATE: Sep 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 1010;
const int MAXE = 100000;
int orig, dest;

struct Edge {
    int v;
    long long c, f; // capa, flow
    Edge *next;
    Edge *rev; // revese edge
};
Edge e_buf[MAXE << 1];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
Edge *e_tail;

int que[MAXV], lev[MAXV];

inline void add_edge(int u, int v, long long c)
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
        for (Edge *e = e_head[u]; e; e = e->next)
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
    }

    return lev[dest] > -1;
}

long long dfs(int u, long long f)
{
    if (u == dest) return f;

    long long res = 0;
    for (Edge *&e = e_work[u]; e; e = e->next)
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            long long tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) break;
        }

    return res;
}

long long dinic()
{
    long long res = 0;
    while (bfs()) {
        memcpy(e_work, e_head, sizeof e_head);
        long long tmp = dfs(orig, LLINF);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        int s, t;
        scanf("%d%d", &s, &t);
        s--; t--;
        orig = s << 1 | 1;
        dest = t << 1 | 1;

        long long ans = LLINF;
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            add_edge(i << 1, i << 1 | 1, v);
            if (i == s || i == t) {
                ans = min(ans, (long long)v);
            }
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            add_edge(u << 1 | 1, v << 1, LLINF);
            add_edge(v << 1 | 1, u << 1, LLINF);
        }

        printf("%I64d\n", min(ans, dinic()));
    }

    return 0;
}
