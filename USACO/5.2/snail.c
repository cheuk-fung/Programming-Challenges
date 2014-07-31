/*
ID: os.idea1
LANG: C
TASK: snail
*/
#include <stdio.h>

FILE *fin, *fout;

const int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int n, m, ans;
int map[200][200];

void move_x(int, int, int);
void move_y(int, int, int);

void search(int x, int y, int d, int step)
{
    map[x][y] = 2;
    ans = step > ans ? step : ans;

    int dx = x + dir[d][0], dy = y + dir[d][1];
    if (dx < 0 || dx >= n) {
        move_y(x, y, step);

        map[x][y] = 0;
        return ;
    }
    if (dy < 0 || dy >= n) {
        move_x(x, y, step);

        map[x][y] = 0;
        return ;
    }

    if(map[dx][dy] == 1) {
        if (d == 0 || d == 2) move_y(x, y, step);
        else move_x(x, y, step);

        map[x][y] = 0;
        return ;
    }
    if (map[dx][dy] == 2) {
        map[x][y] = 0;
        return ;
    }

    search(dx, dy, d, step + 1);

    map[x][y] = 0;
}

void move_x(int x, int y, int step)
{
    if (x > 0 && !map[x - 1][y])
        search(x - 1, y, 0, step + 1);
    if (x + 1 < n && !map[x + 1][y])
        search(x + 1, y, 2, step + 1);
}

void move_y(int x, int y, int step)
{
    if (y > 0 && !map[x][y - 1])
        search(x, y - 1, 3, step + 1);
    if (y + 1 < n && !map[x][y + 1])
        search(x, y + 1, 1, step + 1);
}

int main()
{
    fin = fopen("snail.in", "r");
    fout = fopen("snail.out", "w");

    fscanf(fin, "%d%d", &n, &m);

    int i;
    for (i = 0; i < m; i++) {
        char c;
        int t;
        fscanf(fin, " %c%d", &c, &t);
        map[t - 1][c - 'A'] = 1;
    }

    if (!map[0][1]) search(0, 0, 1, 1);
    if (!map[1][0]) search(0, 0, 2, 1);

    fprintf(fout, "%d\n", ans);

    return 0;
}
