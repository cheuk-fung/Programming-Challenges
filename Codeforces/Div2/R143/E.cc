#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

const int MOD = 1000000007;
const int MAXN = 100010;
const int MAXBIT = 20;

int two[MAXN], depth[MAXN], dist[MAXN];
int parent[MAXN][MAXBIT];

vector<int> e[MAXN], ne[MAXN];
stack<int> S;
bool instack[MAXN];
int tms, bcccnt;
int dfn[MAXN], low[MAXN], bccid[MAXN], bccsize[MAXN];

void tarjandfs(int u, int p)
{
    dfn[u] = low[u] = tms++;
    S.push(u);
    instack[u] = true;

    for (int i = 0; i < SIZE(e[u]); i++) {
        int v = e[u][i];
        if (v == p) continue;
        if (dfn[v] == -1) {
            tarjandfs(v, u);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        int v;
        do {
            v = S.top();
            S.pop();
            instack[v] = false;
            bccid[v] = bcccnt;
            bccsize[bcccnt]++;
        } while (v != u);
        bcccnt++;
    }
}

void tarjan(int n)
{
    tms = bcccnt = 0;
    memset(dfn, 0xff, sizeof dfn);
    memset(bccsize, 0, sizeof bccsize);
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjandfs(i, -1);
        }
    }
}

void getparent(int u, int p, int dep)
{
    depth[u] = dep;
    dist[u] = dist[p] + (bccsize[u] > 1);
    for (int i = 0; i < SIZE(ne[u]); i++) {
        int v = ne[u][i];
        if (v == p || depth[v] != 0) continue;
        parent[v][0] = u;
        for (int j = 1; j < MAXBIT; j++) {
            parent[v][j] = parent[parent[v][j - 1]][j - 1];
        }
        getparent(v, u, dep + 1);
    }
}

int lca(int x, int y)
{
    if (depth[x] < depth[y]) swap(x, y);
    if (depth[x] > depth[y]) {
        int diff = depth[x] - depth[y];
        for (int i = 0; i < MAXBIT; i++) {
            if (diff & (1 << i)) {
                x = parent[x][i];
            }
        }
    }
    if (x != y) {
        for (int i = MAXBIT - 1; i >= 0; i--) {
            if (parent[x][i] != parent[y][i]) {
                x = parent[x][i];
                y = parent[y][i];
            }
        }
        x = parent[x][0];
        y = parent[y][0];
    }
    return x;
}

int main()
{
    ios_base::sync_with_stdio(false);

    two[0] = 1;
    for (int i = 1; i < MAXN; i++) two[i] = two[i - 1] * 2 % MOD;

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    tarjan(n);

    for (int u = 0; u < n; u++) {
        for (int i = 0; i < SIZE(e[u]); i++) {
            int v = e[u][i];
            if (bccid[u] != bccid[v]) {
                ne[bccid[u]].push_back(bccid[v]);
                ne[bccid[v]].push_back(bccid[u]);
            }
        }
    }
    getparent(0, 0, 0);

    int k;
    cin >> k;
    while (k--) {
        int a, b;
        cin >> a >> b;
        a = bccid[a - 1];
        b = bccid[b - 1];
        int p = lca(a, b);
        int cnt = dist[a] + dist[b] - dist[p] * 2 + (bccsize[p] > 1);
        cout << two[cnt] << endl;
    }

    return 0;
}

