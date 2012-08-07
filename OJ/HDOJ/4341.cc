/*
 *  SRC: HDOJ 4341
 * PROB: Gold miner
 * ALGO: DP
 * DATE: Aug 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class Disjoint_set {
    private:
        int a[300];

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

struct Gold {
    int x, y, t, v;

    bool operator<(const Gold &o) const
    {
        return x * x + y * y < o.x * o.x + o.y * o.y;
    }
} g[300];
vector<Gold> ng[300];
int f[50000];

inline bool coline(int a, int b)
{
    return g[a].x * g[b].y == g[a].y * g[b].x;
}

int main()
{
    int n, T, tasks = 1;
    while (~scanf("%d%d", &n, &T)) {
        ds.reset();
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &g[i].x, &g[i].y, &g[i].t, &g[i].v);
            ng[i].clear();
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (coline(i, j)) ds.join(i, j);
            }
        }

        for (int i = 0; i < n; i++) {
            ng[ds.find(i)].push_back(g[i]);
        }
        for (int i = 0; i < n; i++) {
            sort(ng[i].begin(), ng[i].end());
            for (int j = 1; j < (int)ng[i].size(); j++) {
                ng[i][j].t += ng[i][j - 1].t;
                ng[i][j].v += ng[i][j - 1].v;
            }
        }

        int ans = 0;
        memset(f, 0, sizeof f);
        for (int i = 0; i < n; i++) {
            if (ng[i].empty()) continue;
            for (int j = T; j >= 0; j--) {
                for (int k = 0; k < (int)ng[i].size(); k++) {
                    if (j - ng[i][k].t >= 0) {
                        f[j] = max(f[j], f[j - ng[i][k].t] + ng[i][k].v);
                        ans = max(ans, f[j]);
                    }
                }
            }
        }

        printf("Case %d: %d\n", tasks++, ans);
    }

    return 0;
}

