/*
 *  SRC: POJ 1946
 * PROB: Cow Cycling
 * ALGO: DP
 * DATE: Oct 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int f[22][110][110];

int main()
{
    int n, e, d;
    scanf("%d%d%d", &n, &e, &d);
    memset(f, 0x3f, sizeof f);
    f[0][0][0] = 0;
    int ans = INF;
    for (int i = 1; i <= n; i++) {             // cow
        for (int j = i; j <= d; j++) {         // time
            for (int k = 0; k <= d; k++) {     // dist
                for (int l = 0; l <= k; l++) { // speed
                    int now = INF;
                    if (f[i - 1][j - 1][k - l] <= e) now = k - l;
                    f[i][j][k] = min(f[i][j][k], min(now, f[i][j - 1][k - l]) + l * l);
                }
                if (f[i][j][k] > e) break;
                if (k == d) ans = min(ans, j);
            }
            if (j >= ans) break;
        }
    }
    printf("%d\n", ans == INF ? 0 : ans);

    return 0;
}

