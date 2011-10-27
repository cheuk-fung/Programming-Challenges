/*
 *  SRC: POJ 3661
 * PROB: Running
 * ALGO: DP
 * DATE: Jul 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int d[10010];
int f[510][510];

inline int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", d + i);

    int maxWhenZero = 0;
    f[0][0] = 0;
    f[0][1] = d[0];
    for (int i = 1; i < n; i++) {
        f[i % (m + 1)][0] = maxWhenZero;
        for (int j = 1; j <= m; j++) {
            f[i % (m + 1)][j] = f[(i - 1) % (m + 1)][j - 1] + d[i];
            if (i >= j)
                f[i % (m + 1)][0] = max(f[i % (m + 1)][0], f[(i - j) % (m + 1)][j]);
        }
        maxWhenZero = max(maxWhenZero, f[i % (m + 1)][0]);
    }

    printf("%d\n", maxWhenZero);

    return 0;
}
