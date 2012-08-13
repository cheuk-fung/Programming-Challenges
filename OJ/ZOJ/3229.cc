/*
 *  SRC: ZOJ 3229
 * PROB: Shoot the Bullet
 * ALGO: Network flow
 * DATE: Aug 13, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 1500;
const int MAXE = 1000000;

struct Edge {
    int v, c, f;
    bool clear;
    Edge *next, *rev;
} ebuf[MAXE];
Edge *ehead[MAXV], *ework[MAXV], *etail;
int que[MAXV], lev[MAXV];

inline void addedge(int u, int v, int c, bool clear = false)
{
    *etail = (Edge){v, c, 0, clear, ehead[u]};
    ehead[u] = etail++;
    *etail = (Edge){u, 0, 0, clear, ehead[v]};
    ehead[v] = etail++;
    ehead[u]->rev = ehead[v];
    ehead[v]->rev = ehead[u];
}

bool bfs(int s, int t)
{
    memset(lev, 0xff, sizeof lev);

    int *head = que, *tail = que;
    *tail++ = s;
    lev[s] = 0;
    while (head != tail) {
        int u = *head++;
        for (Edge *e = ehead[u]; e; e = e->next) {
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
        }
    }
    return lev[s] != -1;
}

int dfs(int u, int f, int t)
{
    if (u == t) return f;

    int res = 0;
    for (Edge *&e = ework[u]; e; e = e->next) {
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int r = dfs(e->v, min(f - res, e->c - e->f), t);
            res += r;
            e->f += r;
            e->rev->f = -e->f;
            if (res == f) break;
        }
    }
    return res;
}

int dinic(int s, int t)
{
    int res = 0;
    while (bfs(s, t)) {
        memcpy(ework, ehead, sizeof ehead);
        int r = dfs(s, INF, t);
        if (!r) break;
        res += r;
    }
    return res;
}

int main()
{
    // printf("%d\n", sizeof ebuf / 1024);
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(ehead, 0, sizeof ehead);
        etail = ebuf;

        int s = MAXV - 1, t = MAXV - 2;
        int vs = MAXV - 3, vt = MAXV - 4;
        int vsum = 0;
        for (int i = 0; i < m; i++) {
            int G;
            scanf("%d", &G);
            addedge(s, i, INF);
            addedge(s, vt, G, true);
            addedge(vs, i, G, true);
            vsum += G;
        }

        Edge *outputfirst = etail;
        for (int i = 0; i < n; i++) {
            int C, D;
            scanf("%d%d", &C, &D);
            addedge(m + i, t, D);
            for (int j = 0; j < C; j++) {
                int T, L, R;
                scanf("%d%d%d", &T, &L, &R);
                addedge(T, m + i, R - L);
                addedge(T, vt, L, true);
                addedge(vs, m + i, L, true);
                vsum += L;
            }
        }
        Edge *outputlast = etail;
        addedge(t, s, INF, true);

        int r = dinic(vs, vt);
        if (r != vsum) {
            puts("-1");
        } else {
            for (Edge *e = ebuf; e != etail; e++) {
                if (e->clear) e->f = e->c;
            }
            dinic(s, t);
            int ans = 0;
            for (Edge *e = ehead[s]; e; e = e->next) {
                ans += e->f;
            }
            printf("%d\n", ans);
            do {
                if (outputfirst->v == t) outputfirst += 2;
                printf("%d\n", outputfirst->f + (outputfirst + 2)->c);
                outputfirst += 6;
            } while (outputfirst != outputlast);
        }
        putchar(10);
    }

    return 0;
}

