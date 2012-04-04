/*
 *  SRC: NKOJ 2187
 * PROB: 上机考试
 * ALGO: DP
 * DATE: Apr 03, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

long long f[12][12];
long long g[12][12];
long long pow10[12];

int main()
{
    int n, k, x;
    scanf("%d%d%d", &n, &k, &x);

    pow10[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow10[i] = pow10[i - 1] * 10;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            g[i][j] = x % pow10[j] / pow10[i - 1];
        }
    }

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(k, i); j++) {
            for (int kk = 0; kk < i; kk++) {
                f[i][j] = max(f[i][j], f[kk][j - 1] * g[kk + 1][i]);
            }
        }
    }

    printf("%lld\n", f[n][k]);

    return 0;
}

