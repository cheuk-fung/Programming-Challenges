/*
 *  SRC: HDOJ 4009
 * PROB: Transfer water
 * ALGO: Chu-Liu/Edmonds Algorithm (Directed Minimum Spanning Tree)
 * DATE: Sep 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

struct Edge {
    int u, v, d;
} ebuf[MAXN * MAXN];
Edge *etail;

struct Node {
    int v, d;
} prev[MAXN];

struct Point {
    int x, y, z;
} pnt[MAXN];

int vis[MAXN], idx[MAXN];

inline void addedge(int u, int v, int d) { *etail++ = (Edge){u, v, d}; }
inline int dist(int u, int v) { return abs(pnt[u].x - pnt[v].x) + abs(pnt[u].y - pnt[v].y) + abs(pnt[u].z - pnt[v].z); }

int chu_liu(int root, int n)
{
    int res = 0;
    while (1) {
        memset(prev, 0x3f, sizeof prev);
        prev[root].d = 0;
        for (Edge *e = ebuf; e != etail; e++) {
            if (e->d < prev[e->v].d) {
                prev[e->v].v = e->u;
                prev[e->v].d = e->d;
            }
        }

        for (int i = 0; i < n; i++) {
            if (i != root && prev[i].d == INF) {
                return -1;
            }
        }

        int cnt = 0;
        memset(idx, 0xff, sizeof idx);
        memset(vis, 0xff, sizeof vis);
        for (int i = 0; i < n; i++) {
            res += prev[i].d;

            int u = i;
            // i might not be in the circle
            while (vis[u] != i && idx[u] == -1 && u != root) {
                vis[u] = i;
                u = prev[u].v;
            }
            if (u != root && idx[u] == -1) {
                for (int v = prev[u].v; v != u; v = prev[v].v) {
                    idx[v] = cnt;
                }
                idx[u] = cnt++;
            }
        }

        if (cnt == 0) break;
        for (int i = 0; i < n; i++) {
            if (idx[i] == -1) {
                idx[i] = cnt++;
            }
        }

        Edge *tetail = etail;
        etail = ebuf;
        for (Edge *e = ebuf; e != tetail; e++) {
            if (idx[e->u] != idx[e->v]) {
                addedge(idx[e->u], idx[e->v], e->d - prev[e->v].d);
            }
        }

        n = cnt;
        root = idx[root];
    }

    return res;
}

int main()
{
    int n, X, Y, Z;
    while (scanf("%d%d%d%d", &n, &X, &Y, &Z), n || X || Y || Z) {
        etail = ebuf;

        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &pnt[i].x, &pnt[i].y, &pnt[i].z);
            addedge(0, i, X * pnt[i].z);
        }
        for (int u = 1; u <= n; u++) {
            int k;
            scanf("%d", &k);
            for (int i = 0; i < k; i++) {
                int v;
                scanf("%d", &v);
                if (v == u) continue;
                addedge(u, v, Y * dist(u, v) + (pnt[u].z < pnt[v].z ? Z : 0));
            }
        }

        int r = chu_liu(0, n + 1);
        printf("%d\n", r);
    }

    return 0;
}

