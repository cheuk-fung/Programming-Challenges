/*
 *  SRC: HDOJ 2452
 * PROB: Navy maneuvers
 * ALGO: DP
 * DATE: Feb 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::min;
using std::pair;

const int INF = 0x3f3f3f3f;

int n, m, f;

vector<int> e[10010];
int d[10010], deg[10010];
pair<int, int> g[10010];

pair<int, int> dp(int p)
{
    if (g[p].first != -1) return g[p];

    if (e[p].size() == 0)
        return g[p] = pair<int, int>(d[p], d[p]);

    g[p].first = 0;
    g[p].second = INF;
    for (int i = 0; i < e[p].size(); i++) {
        g[p].first = max(g[p].first, dp(e[p][i]).second);
        g[p].second = min(g[p].second, dp(e[p][i]).first);
    }

    g[p].first += d[p];
    g[p].second += d[p];

    return g[p];
}

int main()
{
    while (~scanf("%d%d%d", &n, &m, &f)) {
        for (int i = 1; i <= n; i++) {
            e[i].clear();
            deg[i] = 0;
            g[i].first = g[i].second = -1;
        }
        for (int i = 1; i <= n; i++) scanf("%d", d + i);
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            deg[v]++;
        }
        int root = 0;
        for (int i = 1; i <= n; i++)
            if (!deg[i]) {
                root = i;
                break;
            }

        puts(dp(root).first >= f ? "Victory" : "Glory");
    }

    return 0;
}
