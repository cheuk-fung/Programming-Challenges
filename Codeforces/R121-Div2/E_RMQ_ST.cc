#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int>::const_iterator vci;
const int MAXN = 100010;

class BIT {
    public:
        static const int bound = MAXN << 1;
        int c[bound << 1];
        int lowbit(int x) { return x & -x; }
        void update(int x, int v)
        {
            for ( ; x < bound; c[x] += v, x += lowbit(x)) ;
        }
        int sum(int x)
        {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }
};
BIT bit;

struct Edge {
    int u, v;

    Edge(int _u, int _v) : u(_u), v(_v) { }
};

vector<Edge> e;
vector<int> edge[MAXN];
int idx, cnt, dfs_cnt;
int father[MAXN], dist[MAXN], label[MAXN], rev_label[MAXN], pos[MAXN], seq[MAXN << 1];
int dfs_in[MAXN], dfs_out[MAXN];
int mn[20][MAXN << 1];

void dfs(int u, int depth)
{
    dist[u] = depth;
    label[u] = cnt;
    rev_label[cnt++] = u;
    pos[label[u]] = idx;
    seq[idx++] = label[u];

    dfs_in[u] = dfs_cnt--;

    for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
        if (*v != father[u]) {
            father[*v] = u;
            dfs(*v, depth + 1);
            seq[idx++] = label[u];
        }
    }

    dfs_out[u] = dfs_cnt--;
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

int RMQ_min(int l, int r)
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
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edge[u - 1].push_back(v - 1);
        edge[v - 1].push_back(u - 1);
        e.push_back(Edge(u - 1, v - 1));
    }

    idx = cnt = 0;
    dfs_cnt = 2 * n;
    father[0] = 0;
    dfs(0, 0);
    RMQ_init(seq, idx);

    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        bit.update(dfs_in[u], 1);
        bit.update(dfs_in[v], 1);
        bit.update(dfs_in[RMQ_lca(u, v)], -2);
    }

    for (int i = 0; i < e.size(); i++) {
        int x = (father[e[i].u] == e[i].v ? e[i].u : e[i].v);
        cout << bit.sum(dfs_in[x]) - bit.sum(dfs_out[x]) << " ";
    }

    return 0;
}

