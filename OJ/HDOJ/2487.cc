/*
 *  SRC: HDOJ 2487
 * PROB: Ugly Windows
 * ALGO: NULL
 * DATE: Nov 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int n, m;
char map[110][110];

bool check(char c)
{
    int sx, sy;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] == c) {
                sx = i;
                sy = j;
                goto NEXT_STEP;
            }
    return false;

NEXT_STEP:
    int ex = sx, ey = sy;
    while (ex + 1 < n && map[ex + 1][sy] == c) ex++;
    while (ey + 1 < m && map[sx][ey + 1] == c) ey++;
    if (ex - sx < 2 || ey - sy < 2) return false;

    int tx = sx, ty = sy;
    while (tx + 1 < n && map[tx + 1][ey] == c) tx++;
    while (ty + 1 < m && map[ex][ty + 1] == c) ty++;
    if (tx != ex || ty != ey) return false;

    for (int i = sx + 1; i < ex; i++)
        for (int j = sy + 1; j < ey; j++)
            if (map[i][j] != '.') return false;

    return true;
}

int main()
{
    while (scanf("%d%d", &n, &m), n && m) {
        for (int i = 0; i < n; i++) scanf("%s", map[i]);
        for (char c = 'A'; c <= 'Z'; c++) 
            if (check(c)) putchar(c);
        putchar(10);
    }

    return 0;
}
