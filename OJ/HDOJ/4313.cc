/*
 *  SRC: HDOJ 4313
 * PROB: Matrix
 * ALGO: DP
 * DATE: Jul 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100010;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

struct Edge {
    int v;
    long long d;

    Edge *next;
};
Edge e_buf[MAXN << 1];
Edge *e_head[MAXN];
Edge *e_tail;

bool machine[MAXN];
long long f[MAXN], g[MAXN];

inline void add_edge(int u, int v, long long d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

void dp(int u, int parent)
{
    if (machine[u]) {
        f[u] = 0;
        g[u] = LLINF;
        for (Edge *e = e_head[u]; e; e = e->next) {
            if (e->v == parent) continue;
            dp(e->v, u);
            f[u] += f[e->v] + min(g[e->v], e->d);
        }
    } else {
        f[u] = g[u] = 0;
        for (Edge *e = e_head[u]; e; e = e->next) {
            if (e->v == parent) continue;
            dp(e->v, u);
            f[u] += f[e->v];
            long long d = min(g[e->v], e->d);
            if (d > g[u]) {
                f[u] += g[u];
                g[u] = d;
            } else {
                f[u] += d;
            }
        }
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(machine, false, sizeof machine);
        memset(e_head, 0, sizeof e_head);
        e_tail = e_buf;

        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i < n; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            add_edge(x, y, z);
            add_edge(y, x, z);
        }

        int root = 0;
        for (int i = 0; i < k; i++) {
            scanf("%d", &root);
            machine[root] = true;
        }

        dp(root, -1);
        cout << f[root] << endl;
    }

    return 0;
}

