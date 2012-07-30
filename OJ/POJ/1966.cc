/*
 *  SRC: POJ 1966
 * PROB: Cable TV Network
 * ALGO: Dinic
 * DATE: Jul 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 110;
const int MAXE = 1000;
int orig, dest;

struct Edge {
    int v, c, f;
    Edge *next, *rev;
};
Edge e_buf[MAXE << 1];
Edge *e_head[MAXV], *e_work[MAXV], *e_tail;
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
    lev[orig] = 0;
    int *head = que, *tail = que;
    *tail++ = orig;
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
            if (res == f) break;
        }
    }
    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        memcpy(e_work, e_head, sizeof e_head);
        int r = dfs(orig, INF);
        if (!r) break;
        res += r;
    }
    return res;
}

struct OEdge {
    int u, v;
} oe[MAXE];

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        if (n <= 1 || n * (n - 1) == m * 2) {
            for (int i = 0; i < m; i++) {
                scanf(" (%*d,%*d)");
            }
            printf("%d\n", n);
            continue;
        }

        for (int i = 0; i < m; i++) {
            scanf(" (%d,%d)", &oe[i].u, &oe[i].v);
        }

        int ans = INF;
        orig = n;
        for (dest = 0; dest < n; dest++) {
            memset(e_head, 0, sizeof e_head);
            e_tail = e_buf;
            assert(orig != dest);

            for (int k = 0; k < n; k++) {
                add_edge(k, k + n, 1);
            }
            for (int k = 0; k < m; k++) {
                add_edge(oe[k].u + n, oe[k].v, INF);
                add_edge(oe[k].v + n, oe[k].u, INF);
            }
            int r = dinic();
            ans = min(ans, r);
        }
        printf("%d\n", ans);
    }

    return 0;
}
