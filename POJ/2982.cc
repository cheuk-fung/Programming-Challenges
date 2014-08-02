/*
 *  SRC: POJ 2982
 * PROB: Time Travel
 * ALGO: Memorize Search
 * DATE: Jul 28, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int INF = 0x3f3f3f3f;
int n, m, k;
int f[110][110];
int a[110], b[110], c[110];

inline int fmin(int a, int b)
{
    return a < b ? a : b;
}

int search(int x, int y)
{
    if (f[x][y]) return f[x][y];
    if (x == 0 && y == 0) return 0;

    int res = INF;
    for (int i = 0; i < k; i++)
        if (x - a[i] >= 0 && y - b[i] >= 0 && x - a[i] <= n && y - b[i] <= m)
            res = fmin(res, search(x - a[i], y - b[i]) + c[i]);

    return f[x][y] = res;
}

int main()
{
    while (scanf("%d%d%d", &n, &m, &k), n || m || k) {
        memset(f, 0, sizeof(f));

        for (int i = 0; i < k; i++)
            scanf("%d%d%d", a + i, b + i, c + i);

        search(n, m);
        if (f[n][m] < INF) printf("%d\n", f[n][m]);
        else puts("-1");
    }

    return 0;
}
