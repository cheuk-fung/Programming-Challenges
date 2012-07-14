/*
 *  SRC: POJ 2229
 * PROB: Sumsets
 * ALGO: DP
 * DATE: Jul 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MOD = 1000000000;
int f[1000001];

int main()
{
    int n;
    scanf("%d", &n);
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1];
        if (!(i & 1)) f[i] = (f[i] + f[i / 2]) % MOD;
    }
    printf("%d\n", f[n]);

    return 0;
}

