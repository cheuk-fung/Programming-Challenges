#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 16001;

int n, minimum, size[MAXN];
vector<int> tree[MAXN];
vector<int> miniset;

int walk(int u, int parent)
{
    size[u] = 1;
    int now = 0;
    for (int i = 0; i < (int)tree[u].size(); i++) {
        int v = tree[u][i];
        if (v == parent) continue;
        size[u] += walk(v, u);
        now = max(now, size[v]);
    }

    now = max(now, n - size[u]);
    if (now < minimum) {
        minimum = now;
        miniset.clear();
        miniset.push_back(u);
    } else if (now == minimum) {
        miniset.push_back(u);
    }

    return size[u];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    minimum = n;
    walk(1, 0);
    sort(miniset.begin(), miniset.end());
    printf("%d %d\n", minimum, miniset.size());
    for (int i = 0; i < (int)miniset.size(); i++) {
        printf("%d%c", miniset[i], i + 1 == (int)miniset.size() ? '\n' : ' ');
    }

    return 0;
}
