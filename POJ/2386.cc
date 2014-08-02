/*
 *  SRC: POJ 2386
 * PROB: Lake Counting
 * ALGO: Flood Fill
 * DATE: Jul 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

char map[110][110];
int n, m;

const int dir[8][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1}
};

void dfs(int x, int y)
{
    map[x][y] = '.';
    for (int i = 0; i < 8; i++) {
        int xx = x + dir[i][0], yy = y + dir[i][1];
        if (0 <= xx && xx < n && 0 <= yy && yy < m)
            if (map[xx][yy] == 'W') dfs(xx, yy);
    }
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) scanf("%s", map[i]);

    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] == 'W') {
                dfs(i, j);
                cnt++;
            }

    printf("%d\n", cnt);
}
