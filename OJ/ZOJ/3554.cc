/*
 *  SRC: ZOJ 3554
 * PROB: A Miser Boss
 * ALGO: DP
 * DATE: Aug 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

bool f[2][130][130][130];
int a[50], b[50], c[50];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        memset(f, false, sizeof f);

        int suma = 0, sumb = 0, sumc = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", a + i, b + i, c + i);
            suma += a[i];
            sumb += b[i];
            sumc += c[i];
        }
        f[0][0][0][0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= suma; j++) {
                for (int k = 0; k <= sumb; k++) {
                    for (int l = 0; l <= sumc; l++) {
                        if (j >= a[i] && f[(i - 1) & 1][j - a[i]][k][l]) f[i & 1][j][k][l] = true;
                        if (k >= b[i] && f[(i - 1) & 1][j][k - b[i]][l]) f[i & 1][j][k][l] = true;
                        if (l >= c[i] && f[(i - 1) & 1][j][k][l - c[i]]) f[i & 1][j][k][l] = true;
                    }
                }
            }
            memset(f[(i - 1) & 1], false, sizeof f[(i - 1) & 1]);
        }

        int ans = -1;
        for (int i = 0; i < 130; i++) {
            if (f[n & 1][i][i][i]) {
                ans = i;
                break;
            }
        }
        if (ans == -1) puts("NO");
        else printf("%d\n", ans);
    }

    return 0;
}

