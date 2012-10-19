/*
 *  SRC: POJ 1682
 * PROB: Clans on the Three Gorges
 * ALGO: DP
 * DATE: Oct 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int x[110], y[110], z[110];
int fxz[110][110], fzy[110][110], fyx[110][110];

void dp(int n, int *x, int m, int *y, int (*f)[110])
{
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            f[i][j] = INF;
            if (i - 1 >= 0 && j + 1 < m) f[i][j] = min(f[i][j], f[i - 1][j + 1]);
            if (i - 1 >= 0) f[i][j] = min(f[i][j], f[i - 1][j]);
            if (j + 1 < m)  f[i][j] = min(f[i][j], f[i][j + 1]);
            if (f[i][j] == INF) {
                assert(i == 0 && j == m - 1);
                f[i][j] = 0;
            }
            f[i][j] += abs(x[i] - y[j]);
        }
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++) scanf("%d", x + i);
        for (int i = 0; i < m; i++) scanf("%d", y + i);
        for (int i = 0; i < k; i++) scanf("%d", z + i);

        dp(n, x, k, z, fxz);
        dp(k, z, m, y, fzy);
        dp(m, y, n, x, fyx);

        int ans = INF;
        for (int a = 0; a < n; a++) {
            int a1 = a;
            for (int a2 = a; a2 < n && a2 <= a + 1; a2++) {
                for (int b = 0; b < m; b++) {
                    int b1 = b;
                    for (int b2 = b; b2 < m && b2 <= b + 1; b2++) {
                        for (int c = 0; c < k; c++) {
                            int c1 = c;
                            for (int c2 = c; c2 < k && c2 <= c + 1; c2++) {
                                ans = min(ans, fxz[a1][c2] + fzy[c1][b2] + fyx[b1][a2]);
                                if (a + 1 == n && b == 0) ans = min(ans, fxz[a][c2] + fzy[c1][b]);
                                if (b + 1 == m && c == 0) ans = min(ans, fyx[b][a2] + fxz[a1][c]);
                                if (c + 1 == k && a == 0) ans = min(ans, fzy[c][b2] + fyx[b1][a]);
                            }
                        }
                    }
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

