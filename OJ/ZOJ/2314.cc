/*
 *  SRC: ZOJ 2314
 * PROB: Reactor Cooling
 * ALGO: Network flow
 * DATE: Aug 13, 2012
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
const int MAXV = 210;
const int MAXE = (MAXV * MAXV + 10) << 2;

struct Edge {
    int v, c, f;
    Edge *next, *rev;
};
Edge ebuf[MAXE];
Edge *ehead[MAXV], *ework[MAXV], *etail;
int que[MAXV], lev[MAXV];

inline void addedge(int u, int v, int c)
{
    *etail = (Edge){v, c, 0, ehead[u]};
    ehead[u] = etail++;
    *etail = (Edge){u, 0, 0, ehead[v]};
    ehead[v] = etail++;
    ehead[u]->rev = ehead[v];
    ehead[v]->rev = ehead[u];
}

bool bfs(int orig, int dest)
{
    memset(lev, 0xff, sizeof lev);

    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;
    while (head != tail) {
        int u = *head++;
        for (Edge *e = ehead[u]; e; e = e->next) {
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
        }
    }
    return lev[dest] != -1;
}

int dfs(int u, int f, int dest)
{
    if (u == dest) return f;

    int res = 0;
    for (Edge *&e = ework[u]; e; e = e->next) {
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int tmp = dfs(e->v, min(f - res, e->c - e->f), dest);
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) break;
        }
    }
    return res;
}

int dinic(int orig, int dest)
{
    int res = 0;
    while (bfs(orig, dest)) {
        memcpy(ework, ehead, sizeof ehead);
        int f = dfs(orig, INF, dest);
        if (!f) break;
        res += f;
    }
    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        etail = ebuf;
        memset(ehead, 0, sizeof ehead);

        int n, m;
        scanf("%d%d", &n, &m);

        int orig = 0, dest = n + 1;
        int lsum = 0;
        for (int i = 0; i < m; i++) {
            int u, v, l, c;
            scanf("%d%d%d%d", &u, &v, &l, &c);
            addedge(u, v, c - l);
            addedge(u, dest, l);
            addedge(orig, v, l);
            lsum += l;
        }
        assert((etail - ebuf) % 6 == 0);

        int r = dinic(orig, dest);
        if (r == lsum) {
            puts("YES");
            for (Edge *e = ebuf; e != etail ; e += 6) {
                printf("%d\n", e->f + (e + 2)->c);
            }
        } else {
            puts("NO");
        }

        if (tasks) putchar(10);
    }

    return 0;
}

