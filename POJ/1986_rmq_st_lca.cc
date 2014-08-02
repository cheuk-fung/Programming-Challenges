/*
 *  SRC: POJ 1986
 * PROB: Distance Queries
 * ALGO: RMQ-ST-LCA (Lowest Common Ancestor)
 * DATE: May 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;
using std::swap;

const int MAXN = 40000;

struct Edge {
    int v, d;
    Edge(int _v, int _d) : v(_v), d(_d) { }
};

typedef vector<Edge>::const_iterator vci;
vector<Edge> edge[MAXN];
int idx, cnt;
int father[MAXN], dist[MAXN], label[MAXN], rev_label[MAXN], pos[MAXN], seq[MAXN << 1];
int mn[20][MAXN << 1];

void dfs(int u, int length)
{
    dist[u] = length;
    label[u] = cnt;
    rev_label[cnt++] = u;
    pos[label[u]] = idx;
    seq[idx++] = label[u];

    for (vci e = edge[u].begin(); e != edge[u].end(); e++) {
        if (e->v != father[u]) {
            father[e->v] = u;
            dfs(e->v, length + e->d);
            seq[idx++] = label[u];
        }
    }
}

void RMQ_init(int *a, int n)
{
    memcpy(mn, a, sizeof(int) * n);
    for (int i = 1; 1 << i <= n; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int RMQ_min(int l, int r) // [l, r)
{
    int idx = log2(r - l);
    return min(mn[idx][l], mn[idx][r - (1 << idx)]);
}

int RMQ_lca(int u, int v)
{
    u = label[u];
    v = label[v];
    if (pos[u] > pos[v]) swap(u, v);
    return rev_label[RMQ_min(pos[u], pos[v] + 1)];
}

int main()
{
    int n;
    scanf("%d%*d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, d;
        scanf("%d%d%d%*s", &u, &v, &d);
        edge[u - 1].push_back(Edge(v - 1, d));
        edge[v - 1].push_back(Edge(u - 1, d));
    }

    idx = cnt = 0;
    father[0] = 0;
    dfs(0, 0);
    RMQ_init(seq, idx);

    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        printf("%d\n", dist[u] + dist[v] - dist[RMQ_lca(u, v)] * 2);
    }

    return 0;
}
