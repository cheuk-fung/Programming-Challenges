/*
 *  SRC: POJ
 * TASK: Ant Counting
 * ALGO: DP
 * DATE: 05/26/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MOD = 1e6;

int f[2][100010], tot[1010], cnt[1010];
int t, a, s, b;

int main()
{
    scanf("%d%d%d%d", &t, &a, &s, &b);

    for (int i = 0; i < a; i++) {
        int type;
        scanf("%d", &type);
        cnt[type]++;
    }
    for (int i = 1; i <= t; i++) tot[i] = tot[i - 1] + cnt[i];

    f[0][0] = f[1][0] = 1;
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= tot[i]; j++) {
            f[i % 2][j] = 0;
            for (int k = 0; k <= cnt[i] && j - k >= 0; k++) {
                f[i % 2][j] = (f[i % 2][j] + f[(i - 1) % 2][j - k]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int i = s; i <= b; i++) ans = (ans + f[t % 2][i]) % MOD;
    printf("%d\n", ans);

    return 0;
}

