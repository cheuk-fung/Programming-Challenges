/*
 *  SRC: POJ 2441
 * PROB: Arrange the Bulls
 * ALGO: DP
 * DATE: Jul 17, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int n, m, ans;
int f[2][1 << 20];
int like[30][30], cnt[30];

int main()
{
    scanf("%d%d", &n, &m);

    if (m < n) {
        puts("0");

        return 0;
    }

    for (int i = 0; i < n; i++) {
        int sum;
        scanf("%d", &sum);
        for (int j = 0; j < sum; j++) {
            int t;
            scanf("%d", &t);
            like[i][cnt[i]++] = 1 << (t - 1);
        }
    }

    for (int i = 0; i < cnt[0]; i++)
        f[0][like[0][i]] = 1;

    const int MAX = 1 << m;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < MAX; j++)
            if (f[(i - 1) % 2][j])
                for (int k = 0; k < cnt[i]; k++)
                    if ((j & like[i][k]) == 0)
                        f[i % 2][j | like[i][k]] += f[(i - 1) % 2][j];
        memset(f[(i - 1) % 2], 0, sizeof(f[0]));
    }

    for (int i = 1; i < MAX; i++)
        ans += f[(n - 1) % 2][i];

    printf("%d\n", ans);

    return 0;
}
