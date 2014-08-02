/*
 *  SRC: HDOJ 4309
 * PROB: Seikimatsu Occult Tonneru
 * ALGO: Dinic
 * DATE: Jul 20, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 1000;
const int MAXE = 10000;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v, c, f;
    Edge *next;
    Edge *rev;
};
Edge e_buf[MAXE << 1];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
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

    return lev[dest] > -1;

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
        int tmp = dfs(orig, INF);
        if (tmp) res += tmp;
        else break;
    }
    return res;
}

struct OEdge {
    int u, v, w;
};

OEdge tunnel[MAXE], road[MAXE], bridge[MAXE];
int peo[MAXV];

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) scanf("%d", peo + i);

        int tcnt = 0, rcnt = 0, bcnt = 0;
        for (int i = 0; i < m; i++) {
            int u, v, w, p;
            scanf("%d%d%d%d", &u, &v, &w, &p);
            if (p < 0) {
                tunnel[tcnt++] = (OEdge){u, v, w};
            } else if (p == 0) {
                road[rcnt++] = (OEdge){u, v, w};
            } else {
                bridge[bcnt++] = (OEdge){u, v, w};
            }
        }

        int maxnum = 0, mincost = INF;
        for (int bit = 0, maxbit = 1 << bcnt; bit < maxbit; bit++) {
            memset(e_head, 0, sizeof e_head);
            e_tail = e_buf;

            for (int i = 1; i <= n; i++) {
                add_edge(orig, i, peo[i]);
            }
            for (int i = 0; i < rcnt; i++) {
                add_edge(road[i].u, road[i].v, INF);
            }
            for (int i = 0; i < tcnt; i++) {
                add_edge(tunnel[i].u, n + i + 1, INF);
                add_edge(n + i + 1, tunnel[i].v, INF);
                add_edge(n + i + 1, dest, tunnel[i].w);
            }

            int cost = 0;
            for (int i = 0; i < bcnt; i++) {
                if (bit & (1 << i)) {
                    add_edge(bridge[i].u, bridge[i].v, INF);
                    cost += bridge[i].w;
                } else {
                    add_edge(bridge[i].u, bridge[i].v, 1);
                }
            }

            int flow = dinic();
            if (flow > maxnum) {
                maxnum = flow;
                mincost = cost;
            } else if (flow == maxnum && cost < mincost) {
                mincost = cost;
            }
        }

        if (maxnum) {
            printf("%d %d\n", maxnum, mincost);
        } else {
            puts("Poor Heaven Empire");
        }
    }

    return 0;
}

