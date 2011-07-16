/*
 *  SRC: POJ 1050
 * PROB: To the Max
 * ALGO: DP
 * DATE: Jul 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int n, ans;
int a[110][110], row[110][110], f[110][100];

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);

    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++)
            row[i][k] = row[i][k - 1] + a[i][k];
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = j; k <= n; k++) {
                if (f[j][k] > 0) f[j][k] += row[i][k] - row[i][j - 1];
                else f[j][k] = row[i][k] - row[i][j - 1];
                if (f[j][k] > ans) ans = f[j][k];
            }

    printf("%d\n", ans);

    return 0;
}
