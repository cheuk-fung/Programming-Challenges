/*
 *  SRC: POJ 1330
 * PROB: Nearest Common Ancestors
 * ALGO: LCA
 * DATE: Aug 03, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

const int MAXN = 10010;
vector<int> e[MAXN];
int indeg[MAXN];
int vis[MAXN];

class Disjoint_set {
    private:
        int a[MAXN];
    public:
        void reset() { memset(a, 0xff, sizeof a); }

        int find(int u)
        {
            int r = u;
            while (a[r] >= 0) r = a[r];
            while (a[u] >= 0) {
                int v = a[u];
                a[u] = r;
                u = v;
            }
            return r;
        }

        void join(int u, int v)
        {
            int x = find(u);
            int y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
} ds;

int lca(int u, int parent, int x, int y)
{
    vis[u] = true;
    if (u == x && vis[y]) return ds.find(y);
    if (u == y && vis[x]) return ds.find(x);

    for (int i = 0; i < (int)e[u].size(); i++) {
        int r = lca(e[u][i], u, x, y);
        if (r) return r;
    }

    ds.join(parent, u);

    return 0;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        ds.reset();
        memset(indeg, 0, sizeof indeg);
        memset(vis, 0, sizeof vis);

        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) e[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            indeg[v]++;
        }

        int root = 0;
        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0) {
                root = i;
                break;
            }
        }

        int u, v;
        scanf("%d%d", &u, &v);
        int r = lca(root, 0, u, v);
        printf("%d\n", r);
    }

    return 0;
}

