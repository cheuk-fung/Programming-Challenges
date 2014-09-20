#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

const int MAXN = 2 * 1e5 + 10;

struct Edge {
    int v, d;
};
vector<Edge> tree[MAXN];

int f[MAXN];
int ans;
vector<int> ansset;

int dfs(int u, int parent)
{
    f[u] = 0;
    for (int i = 0; i < SIZE(tree[u]); i++) {
        int v = tree[u][i].v;
        if (v == parent) continue;
        f[u] += dfs(v, u) + tree[u][i].d;
    }
    return f[u];
}

void walk(int u, int parent, int now)
{
    for (int i = 0; i < SIZE(tree[u]); i++) {
        int v = tree[u][i].v;
        if (v == parent) continue;
        int next = now;
        if (tree[u][i].d) next--;
        else next++;
        if (next == ans) {
            ansset.push_back(v);
        } else if (next < ans) {
            ans = next;
            ansset.clear();
            ansset.push_back(v);
        }
        walk(v, u, next);
    }
}


int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back((Edge){v, 0});
        tree[v].push_back((Edge){u, 1});
    }

    ans = dfs(1, 0);
    ansset.push_back(1);

    walk(1, 0, f[1]);

    cout << ans << endl;
    sort(ansset.begin(), ansset.end());
    for (int i = 0; i < SIZE(ansset); i++) cout << ansset[i] << endl;

    return 0;
}

