/*
 *  SRC: NKOJ 1006
 * PROB: Mine Sweeper
 * ALGO: NULL
 * DATE: Aug 26, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int n;
char map[12][13];
char grid[12][12];
int x[] = { -1, -1, -1,  0,  0,  1,  1,  1 };
int y[] = { -1,  0,  1, -1,  1, -1,  0,  1 };

int main()
{
    memset(map, '.', sizeof(map));

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", map[i] + 1);
    getchar();

    bool bomb = 0;
    for (int i = 1; i <= n; i++, getchar())
        for (int j = 1; j <= n; j++) {
            char c = getchar();
            if (c == '.') {  grid[i][j] = '.'; continue; }
            if (map[i][j] == '*') {  bomb = 1; continue; }

            int cnt = 0;
            for (int k = 0; k < 8; k++)
                cnt += (map[i + x[k]][j + y[k]] == '*');
            grid[i][j] = cnt + '0';
        }

    if (bomb) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (map[i][j] == '*') grid[i][j] = '*';
    }

    for (int i = 1; i <= n; i++, putchar(10))
        for (int j = 1; j <= n; j++) putchar(grid[i][j]);
    
    return 0;
}
