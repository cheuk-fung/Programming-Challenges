/*
 *  SRC: POJ 1724
 * PROB: ROADS
 * ALGO: DFS
 * DATE: Jul 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::max;
const int INF = 0x3f3f3f3f;

int best;
int coins, n, r;
int vis[111];

struct Edge {
    int v, l, t;
    Edge *next;
};
Edge e_buf[10010];
Edge *e_head[111];
Edge *e_tail = e_buf;

inline void add_edge(int u, int v, int l, int t)
{
    *e_tail = (Edge){v, l ,t, e_head[u]};
    e_head[u] = e_tail++;
}

void search(int u, int totl, int tott)
{
    if (totl >= best) return ;
    if (tott > coins) return ;
    if (vis[u]) return ;
    if (u == n) {
        best = totl;
        return ;
    }

    vis[u]++;

    for (Edge *e = e_head[u]; e; e = e->next) {
        search(e->v, totl + e->l, tott + e->t);
    }

    vis[u]--;
}

int main()
{
    scanf("%d%d%d", &coins, &n, &r);
    for (int i = 0; i < r; i++) {
        int u, v, l, t;
        scanf("%d%d%d%d", &u, &v, &l, &t);
        add_edge(u, v, l, t);
    }

    best = INF;
    search(1, 0, 0);
    printf("%d\n", best == INF ? -1 : best);

    return 0;
}

