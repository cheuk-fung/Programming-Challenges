/*
 *  SRC: ZOJ 3626
 * PROB: Treasure Hunt I
 * ALGO: Tree DP
 * DATE: Jul 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 110;
const int MAXM = 220;
typedef pair<int, int> pii;

int n, k, m;
int val[MAXN];
vector<pii> e[MAXN];
int f[MAXN][MAXM];

void dp(int u, int parent, int m)
{
    f[u][0] = val[u];
    for (int i = 0; i < (int)e[u].size(); i++) {
        int v = e[u][i].first;
        if (v == parent) continue;
        dp(v, u, m - e[u][i].second);
        for (int j = m; j >= 0; j--) {
            for (int k = j - e[u][i].second; k >= 0; k--) {
                f[u][j] = max(f[u][j], f[u][j - e[u][i].second - k] + f[v][k]);
            }
        }
    }
}

int main()
{
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            e[i].clear();
            scanf("%d", val + i);
        }
        for (int i = 1; i < n; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            e[u].push_back(pii(v, d * 2));
            e[v].push_back(pii(u, d * 2));
        }

        scanf("%d%d", &k, &m);
        memset(f, 0, sizeof f);
        dp(k, 0, m);
        int ans = 0;
        for (int i = 0; i <= m; i++) ans = max(ans, f[k][i]);
        printf("%d\n", ans);
    }

    return 0;
}
