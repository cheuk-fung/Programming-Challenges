/*
 *  SRC: ZOJ 3623
 * PROB: Battle Ships
 * ALGO: DP
 * DATE: Jul 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 50;
const int MAXM = 1000;

struct Ship {
    int t, l;
} ships[MAXN];

int n, l;
int ans;
int f[MAXM][MAXM];

int main()
{
    while (~scanf("%d%d", &n, &l)) {
        int maxt = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &ships[i].t, &ships[i].l);
            ships[i].l = min(ships[i].l, l);
            maxt = max(maxt, ships[i].t);
        }

        memset(f, 0x3f, sizeof f);
        f[0][0] = l;
        for (int i = 1; i <= l + maxt; i++) {
            for (int j = 0; j <= l; j++) {
                for (int k = 0; k < n; k++) {
                    if (i - ships[k].t >= 0 && j - ships[k].l >= 0) {
                        f[i][j] = min(f[i][j], f[i - ships[k].t][j - ships[k].l] - (j - ships[k].l) * ships[k].t);
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 1; i <= l + maxt; i++) {
            for (int j = 1; j <= l; j++) {
                if (f[i][j] <= 0) {
                    ans = min(ans, i);
                    goto OUTPUT;
                }
                ans = min(ans, i + (f[i][j] + j - 1) / j);
            }
        }

OUTPUT:
        printf("%d\n", ans);
    }

    return 0;
}
