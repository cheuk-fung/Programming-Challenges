/*
 *  SRC: POJ 1383
 * PROB: Labyrinth
 * ALGO: DFS
 * DATE: Sep 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

int n, m;
int best, best_x, best_y;
char map[1010][1010];
bool vis[1010][1010];

void search(int x, int y, int lev)
{
    if (lev > best) {
        best = lev;
        best_x = x;
        best_y = y;
    }

    vis[x][y] = true;
    if (x - 1 >= 0 && map[x - 1][y] == '.' && !vis[x - 1][y])
        search(x - 1, y, lev + 1);
    if (x + 1 <  n && map[x + 1][y] == '.' && !vis[x + 1][y])
        search(x + 1, y, lev + 1);
    if (y - 1 >= 0 && map[x][y - 1] == '.' && !vis[x][y - 1])
        search(x, y - 1, lev + 1);
    if (y + 1 <  m && map[x][y + 1] == '.' && !vis[x][y + 1])
        search(x, y + 1, lev + 1);
}

void work()
{
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; i++) scanf("%s", map[i]);

    int x = 1, y = 1;
    while (map[x][y] == '#') {
        if (y + 1 == m) {
            x++;
            y = 1;
        }
        else y++;
    }

    best = 0;
    best_x = x;
    best_y = y;
    memset(vis, 0, sizeof(vis));
    search(x, y, 0);

    memset(vis, 0, sizeof(vis));
    search(best_x, best_y, 0);
    printf("Maximum rope length is %d.\n", best);
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) work();

    return 0;
}
