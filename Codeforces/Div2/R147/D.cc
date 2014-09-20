#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef pair<int, int> pii;
template<class T> inline int SIZE(const T &x) { return x.size(); }

const int MAXN = 1e5 + 10;

vector<int> tree[MAXN];
vector<pii> edge;
map<pii, int> node;
int idx = 1;

void dfs(int u, int p)
{
    if (p != 0) {
        node[pii(p, u)] = idx++;
        printf("2 %d %d\n", p, u);
    }

    for (int i = 0; i < SIZE(tree[u]); i++) {
        int v = tree[u][i];
        if (v == p) continue;
        dfs(v, u);
        if (u == 1) {
            if (i) edge.push_back(pii(node[pii(u, tree[u][i - 1])], node[pii(u, v)]));
        } else {
            edge.push_back(pii(node[pii(p, u)], node[pii(u, v)]));
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    printf("%d\n", n - 1);
    dfs(1, 0);
    assert(SIZE(edge) == n - 2);
    for (int i = 0; i < SIZE(edge); i++) printf("%d %d\n", edge[i].first, edge[i].second);

    return 0;
}

