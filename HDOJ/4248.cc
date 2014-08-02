/*
 *  SRC: HDOJ 4248
 * PROB: A Famous Stone Collector
 * ALGO: Math
 * DATE: Jul 18, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MOD = 1000000007;
const int MAXN = 100 * 100 + 10;

int f[110][MAXN];
int C[110][MAXN];
int a[110], sum[110];

int main()
{
    for (int i = 0; i < MAXN; i++) C[0][i] = 1;
    for (int j = 1; j <= 100; j++) {
        for (int i = 1; i < MAXN; i++) {
            C[j][i] = (C[j - 1][i - 1] + C[j][i - 1]) % MOD;
        }
    }

    int n;
    for (int task = 1; ~scanf("%d", &n); task++) {
        memset(f, 0, sizeof(f));

        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            sum[i] = sum[ i - 1] + a[i];
        }

        f[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int k = 0; k <= a[i]; k++) {
                for (int j = k; j - k <= sum[i - 1]; j++) {
                    f[i][j] = (f[i][j] + (long long)f[i - 1][j - k] * C[k][j]) % MOD;
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= sum[n]; i++) {
            ans = (ans + f[n][i]) % MOD;
        }
        printf("Case %d: %d\n", task, ans);
    }

    return 0;
}

