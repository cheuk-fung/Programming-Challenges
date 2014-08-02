/*
 *  SRC: POJ 1088
 * PROB: 滑雪
 * ALGO: memorize Search
 * DATE: May 10, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int map[200][200], f[200][200];
int R, C;

inline int max(int a, int b)
{
    return a > b ? a : b;
}

int search(int x, int y)
{
    if (f[x][y]) return f[x][y];

    if (x > 0 && map[x - 1][y] > map[x][y]) f[x][y] = max(f[x][y], search(x - 1, y) + 1);
    if (x < R - 1 && map[x + 1][y] > map[x][y]) f[x][y] = max(f[x][y], search(x + 1, y) + 1);
    if (y > 0 && map[x][y - 1] > map[x][y]) f[x][y] = max(f[x][y], search(x, y - 1) + 1);
    if (y < C - 1 && map[x][y + 1] > map[x][y]) f[x][y] = max(f[x][y], search(x, y + 1) + 1);

    if (!f[x][y]) f[x][y] = 1;

    return f[x][y];
}

int main()
{
    scanf("%d%d", &R, &C);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", map[i] + j);

    int ans = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            f[i][j] = search(i, j);
            if (f[i][j] > ans) ans = f[i][j];
        }

    printf("%d\n", ans);

    return 0;
}

