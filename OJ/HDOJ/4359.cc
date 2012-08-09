/*
 *  SRC: HDOJ 4359
 * PROB: Easy Tree DP?
 * ALGO: DP
 * DATE: Aug 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAXN = 361;
const int MOD = 1e9 + 7;

long long f[MAXN][MAXN];
long long g[MAXN][MAXN];
long long C[MAXN][MAXN];

int main()
{
    for (int i = 0; i < MAXN; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    f[1][1] = 1;
    for (int i = 1; i < MAXN; i++) g[1][i] = 1;
    for (int i = 2; i < MAXN; i++) {
        for (int j = 2; j <= i; j++) {
            f[i][j] = f[i - 1][j - 1] * i * 2 % MOD;
            for (int l = 1; l < i - 1; l++) {
                long long d = i * C[i - 2][l] % MOD;
                f[i][j] = (f[i][j] + d * (((f[l][j - 1] * g[i - l - 1][j - 1] % MOD + g[l][j - 1] * f[i - l - 1][j - 1] % MOD - f[l][j - 1] * f[i - l - 1][j - 1] % MOD) % MOD + MOD) % MOD) % MOD) % MOD;
            }
            g[i][j] = (g[i][j - 1] + f[i][j]) % MOD;
        }
        for (int j = i + 1; j < MAXN; j++) {
            g[i][j] = g[i][j - 1];
        }
    }

    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n, d;
        scanf("%d%d", &n, &d);
        printf("Case #%d: %d\n", task, (int)f[n][d]);
    }


    return 0;
}

