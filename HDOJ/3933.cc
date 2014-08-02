/*
 *  SRC: HDOJ 3933
 * PROB: Dark Parth
 * ALGO: DP
 * DATE: Apr 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 0x3f3f3f3f;

using namespace std;

int a[1010];
int f[1010][1010];

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        int lb, la, s;
        scanf("%d%d%d", &lb, &la, &s);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }

        memset(f, 0x3f, sizeof(f));
        f[0][0] = 0;
        for (int j = 1; j <= n; j++) {
            f[0][j] = f[0][j - 1] + a[j];
        }
        for (int i = 1; i <= s; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = f[i][j - 1] + a[j];
                for (int k = la; k <= lb && j - k >= 0; k++) {
                    f[i][j] = min(f[i][j], f[i - 1][j - k]);
                }
            }
        }

        int ans = INF;
        for (int i = 0; i <= s; i++) {
            ans = min(ans, f[i][n]);
        }

        printf("%d\n", ans);
    }

    return 0;
}

