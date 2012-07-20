/*
 *  SRC: HDOJ 4301
 * PROB: Divide Chocolate
 * ALGO: DP
 * DATE: Jul 20, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MOD = 100000007;

int f[1001][2001][2];

int main()
{
    f[1][1][1] = 1;
    f[1][2][0] = 1;
    for (int i = 2; i <= 1000; i++) {
        f[i][1][1] = 1;
        for (int j = 2; j <= i << 1; j++) {
            f[i][j][0] = (1ll * f[i - 1][j - 2][0] + f[i - 1][j - 2][1] + (f[i - 1][j - 1][0] + f[i - 1][j - 1][1]) * 2ll + f[i - 1][j][0]) % MOD;
            f[i][j][1] = (1ll * f[i - 1][j - 1][0] + f[i - 1][j - 1][1] + f[i - 1][j][0] * 2ll + f[i - 1][j][1]) % MOD;
        }
    }

    int task;
    scanf("%d", &task);
    while (task--) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%d\n", (f[n][k][0] + f[n][k][1]) % MOD);
    }

    return 0;
}

