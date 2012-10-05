/*
 *  SRC: ZOJ 3506
 * PROB: Cut the Tree
 * ALGO: Tree DP
 * DATE: Oct 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, ans;
int w[1010], size[1010];
int f[1010][22];
vector<int> tree[1010];

void dp(int u, int fa)
{
    size[u] = 1;
    if ((fa == -1 && tree[u].size() == 0) || (fa != -1 && tree[u].size() == 1)) {
        f[u][0] = w[u];
        if (m != 0) ans = min(ans, f[u][0]);
        return ;
    }

    f[u][0] = 0;
    for (int i = 0; i < (int)tree[u].size(); i++) {
        int v = tree[u][i];
        if (v == fa) continue;

        dp(v, u);
        size[u] += size[v];

        for (int j = min(m, size[v]); j > 0; j--) {
            f[v][j] = min(f[v][j], 0);
        }

        for (int j = m; j >= 0; j--) {
            f[u][j] += f[v][0];
            for (int k = 1; k <= m && k <= j; k++) {
                f[u][j] = min(f[u][j], f[u][j - k] + f[v][k]);
            }
        }
    }

    for (int i = 0; i <= m && f[u][i] < INF; i++) {
        f[u][i] += w[u];
        if (i != m && n - size[u] + i >= m) {
            ans = min(ans, f[u][i]);
        }
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n; i++) tree[i].clear();
        for (int i = 0; i < n; i++) scanf("%d", w + i);
        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--; y--;
            tree[x].push_back(y);
            tree[y].push_back(x);

        }

        ans = INF;
        memset(f, 0x3f, sizeof f);
        dp(0, -1);
        ans = min(ans, f[0][m]);
        int mn = ans;

        for (int i = 0; i < n; i++) w[i] *= -1;
        ans = INF;
        memset(f, 0x3f, sizeof f);
        dp(0, -1);
        ans = min(ans, f[0][m]);
        int mx = -ans;

        printf("%d %d\n", mn, mx);
    }

    return 0;
}

