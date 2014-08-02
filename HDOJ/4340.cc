/*
 *  SRC: HDOJ 4340
 * PROB: Capturing a country
 * ALGO: Tree DP
 * DATE: Aug 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 110;

vector<int> e[MAXN];
int Av[MAXN], Bv[MAXN];
int Af[MAXN], Ah[MAXN], Bf[MAXN], Bh[MAXN];

void dp(int u, int parent)
{
    bool leaf = true;
    for (int i = 0; i < (int)e[u].size(); i++) {
        int v = e[u][i];
        if (v != parent) {
            leaf = false;
            dp(v, u);
            Af[u] += min(Ah[v], Bf[v]);
            Ah[u] += min(Ah[v], Bf[v]);
            Bf[u] += min(Af[v], Bh[v]);
            Bh[u] += min(Af[v], Bh[v]);
        }
    }
    Af[u] += Av[u];
    Ah[u] += Av[u] / 2;
    Bf[u] += Bv[u];
    Bh[u] += Bv[u] / 2;

    if (!leaf) {
        for (int i = 0; i < (int)e[u].size(); i++) {
            int v = e[u][i];
            if (v != parent) {
                int taf = Af[v] + Av[u] / 2, tbf = Bf[v] + Bv[u] / 2;
                for (int j = 0; j < (int)e[u].size(); j++) {
                    int tv = e[u][j];
                    if (tv != parent && tv != v) {
                        taf += min(Ah[tv], Bf[tv]);
                        tbf += min(Af[tv], Bh[tv]);
                    }
                }
                Af[u] = min(Af[u], taf);
                Bf[u] = min(Bf[u], tbf);
            }
        }
    }
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        memset(Af, 0, sizeof Af);
        memset(Ah, 0, sizeof Ah);
        memset(Bf, 0, sizeof Bf);
        memset(Bh, 0, sizeof Bh);
        for (int i = 0; i <= n; i++) e[i].clear();

        for (int i = 1; i <= n; i++) {
            scanf("%d", Av + i);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", Bv + i);
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }

        dp(1, 0);

        printf("%d\n", min(Af[1], Bf[1]));
    }

    return 0;
}

