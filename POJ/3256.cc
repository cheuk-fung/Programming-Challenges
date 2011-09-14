/*
 *  SRC: POJ 3256
 * PROB: Cow Picnic
 * ALGO: Flood Fill
 * DATE: Sep 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;
typedef vector<int>::const_iterator vci;

int cow[110], cnt[1010];
vector<int> e[1010];
bool vis[1010];

void floodfill(int u)
{
    cnt[u]++;
    vis[u] = true;
    for (vci v = e[u].begin(); v != e[u].end(); v++)
        if (!vis[*v]) floodfill(*v);
}

int main()
{
    int k, n, m;
    scanf("%d%d%d", &k, &n, &m);
    for (int i = 0; i < k; i++) scanf("%d", cow + i);
    for (int i = 0, a, b; i < m; i++) {
        scanf("%d%d", &a, &b);
        e[a].push_back(b);
    }

    for (int i = 0; i < k; i++) {
        memset(vis, 0, sizeof(vis));
        floodfill(cow[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (cnt[i] == k) ans++;

    printf("%d\n", ans);

    return 0;
}
