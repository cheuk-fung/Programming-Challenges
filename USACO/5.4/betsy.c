/*
ID: os.idea1
LANG: C
TASK: betsy
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;

const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int n;
int cnt;
int vis[10][10];

int check(int x, int y)
{
    if (x == n - 1 && y == 0) return 0;

    int i, cnt = 0;
    for (i = 0; i < 4; i++) {
        int xx = x + dir[i][0], yy = y + dir[i][1];
        if (!(0 <= xx && xx < n)) continue;
        if (!(0 <= yy && yy < n)) continue;
        if (!vis[xx][yy]) cnt++;
    }

    return cnt == 1;
}

void dfs(int x, int y, int vis_cnt)
{
    if (x == n - 1 && y == 0) {
        if (vis_cnt == n * n) cnt++;
        return ;
    }

    vis[x][y] = 1;

    int i;
    int can_vis_cnt = 0, can_vis[4];
    for (i = 0; i < 4; i++) {
        int xx = x + dir[i][0], yy = y + dir[i][1];
        if (!(0 <= xx && xx < n)) continue;
        if (!(0 <= yy && yy < n)) continue;
        if (!vis[xx][yy])
            can_vis[can_vis_cnt++] = i;
    }

    if (can_vis_cnt == 0) return ;
    if (can_vis_cnt == 1)
        dfs(x + dir[can_vis[0]][0], y + dir[can_vis[0]][1], vis_cnt + 1);
    else {
        int must_vis_cnt = 0, must_vis[4];
        for (i = 0; i < can_vis_cnt; i++)
            if (check(x + dir[can_vis[i]][0], y + dir[can_vis[i]][1]))
                must_vis[must_vis_cnt++] = can_vis[i];

        if (must_vis_cnt == 0) {
            for (i = 0; i < can_vis_cnt; i++)
                dfs(x + dir[can_vis[i]][0], y + dir[can_vis[i]][1], vis_cnt + 1);
        }
        else if (must_vis_cnt == 1)
            dfs(x + dir[must_vis[0]][0], y + dir[must_vis[0]][1], vis_cnt + 1);
    }

    vis[x][y] = 0;
}

int main()
{
    fin  = fopen("betsy.in", "r");
    fout = fopen("betsy.out", "w");

    fscanf(fin, "%d", &n);
    dfs(0, 0, 1);
    fprintf(fout, "%d\n", cnt);

    return 0;
}
