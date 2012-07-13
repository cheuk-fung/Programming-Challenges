/*
 *  SRC: POJ 2044
 * PROB: Weather Forecast
 * ALGO: Memorize Search
 * DATE: Jul 13, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int dir[9][2] = {
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 1},
    {0, 2},
    {-1, 0},
    {-2, 0},
    {0, -1},
    {0, -2}
};

int days;
int mat[366][4][4];
int f[366][3][3][8][8][8][8];

bool in_cloud(int cx, int cy, int x, int y)
{
    return cx <= x && x <= cx + 1 && cy <= y && y <= cy + 1;
}

bool check(int day, int cx, int cy, int *a, int *b, int *c, int *d)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mat[day][i][j] && in_cloud(cx, cy, i ,j)) return false;
        }
    }

    if (in_cloud(cx, cy, 0, 0)) *a = 0; else (*a)++;
    if (in_cloud(cx, cy, 0, 3)) *b = 0; else (*b)++;
    if (in_cloud(cx, cy, 3, 0)) *c = 0; else (*c)++;
    if (in_cloud(cx, cy, 3, 3)) *d = 0; else (*d)++;

    return true;
}

bool search(int day, int cx, int cy, int a, int b, int c, int d)
{
    if (cx < 0 || cx >= 3 || cy < 0 || cy >= 3) return false;
    if (f[day][cx][cy][a][b][c][d] != -1) return false;
    if (a == 7 || b == 7 || c == 7 || d == 7) return f[day][cx][cy][a][b][c][d] = false;
    if (day == days) return true;

    int da = a, db = b, dc = c, dd = d;
    if (!check(day, cx, cy, &da, &db, &dc, &dd)) return f[day][cx][cy][a][b][c][d] = false;

    for (int i = 0; i < 9; i++) {
        if (search(day + 1, cx + dir[i][0], cy + dir[i][1], da, db, dc, dd))
            return true;
    }

    return f[day][cx][cy][a][b][c][d] = false;
}

int main()
{
    while (scanf("%d", &days), days) {
        for (int i = 0; i < days; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    scanf("%d", &mat[i][j][k]);

        memset(f, 0xff, sizeof(f));
        puts(search(0, 1, 1, 0, 0, 0, 0) ? "1" : "0");
    }

    return 0;
}

