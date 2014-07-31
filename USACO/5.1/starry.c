/*
ID: os.idea1
LANG: C
TASK: starry
*/

#include <stdio.h>
#include <string.h>

FILE *fin, *fout;

int n, m, cnt;
int min_x, max_x, min_y, max_y;
char map[111][111];
char tmp[111][111];
int  vis[111][111];

struct Star {
    int r, c;
    char pic[8][111][111];
} cluster[26];

inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void floodfill(int x, int y, int x0, int y0)
{
    if (x < 0 || x >= n) return ;
    if (y < 0 || y >= m) return ;
    if (map[x][y] == '0' || vis[x][y]) return ;

    vis[x][y] = 1;
    map[x][y] = '2';

    min_x = x < min_x ? x : min_x;
    min_y = y < min_y ? y : min_y;
    max_x = x > max_x ? x : max_x;
    max_y = y > max_y ? y : max_y;

    floodfill(x - 1, y, x0, y0);
    floodfill(x + 1, y, x0, y0);
    floodfill(x, y - 1, x0, y0);
    floodfill(x, y + 1, x0, y0);
    floodfill(x - 1, y - 1, x0, y0);
    floodfill(x - 1, y + 1, x0, y0);
    floodfill(x + 1, y - 1, x0, y0);
    floodfill(x + 1, y + 1, x0, y0);
}

inline int check(int p, int x0, int y0, int r, int c)
{
    int offset = 0, begin, step;
    if (r == cluster[p].r && c == cluster[p].c) offset |= 1;
    if (r == cluster[p].c && c == cluster[p].r) offset |= 2;

    switch (offset) {
        case 0: return 0;
        case 1: begin = 0; step = 2; break;
        case 2: begin = 1; step = 2; break;
        case 3: begin = 0; step = 1; break;
    }

    int i, j, k;
    for (i = begin; i < 8; i += step) {
        for (j = 0; j < r; j++) {
            for (k = 0; k < c; k++)
                if (tmp[j][k] != cluster[p].pic[i][j][k]) break;
            if (k != c) break;
        }
        if (j == r) {
            for (j = 0; j < r; j++)
                for (k = 0; k < c; k++)
                    if (tmp[j][k] == '2')
                        map[x0 + j][y0 + k] = 'a' + p;

            return 1;
        }
    }

    return 0;
}

inline void add_cluster(int x0, int y0, int r, int c)
{
    cluster[cnt].r = r;
    cluster[cnt].c = c;

    int i, j, k;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++) {
            if (tmp[i][j] == '2') {
                cluster[cnt].pic[0][i][j] = '2';
                map[x0 + i][y0 + j] = 'a' + cnt;
            }
            else cluster[cnt].pic[0][i][j] = '0';
        }

    for (k = 1; k < 4; k++) {
        for (i = 0; i < c; i++)
            for (j = 0; j < r; j++)
                cluster[cnt].pic[k][i][j] = cluster[cnt].pic[k - 1][r - 1 - j][i];

        swap(&r, &c);
    }

    swap(&r, &c);
    for (k = 4; k < 8; k++) {
        for (i = 0; i < r; i++)
            for (j = 0; j < c; j++)
                cluster[cnt].pic[k][i][j] = cluster[cnt].pic[k - 4][i][c - 1 - j];

        swap(&r, &c);
    }

    cnt++;
}

int main()
{
    fin = fopen("starry.in", "r");
    fout = fopen("starry.out", "w");

    fscanf(fin, "%d%d", &m, &n);

    int i, j, k;
    for (i = 0; i < n; i++) fscanf(fin, "%s", map[i]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            if (vis[i][j] || map[i][j] == '0') continue;

            min_x = min_y = 111;
            max_x = max_y = 0;
            floodfill(i, j, i, j);

            int r = max_x - min_x + 1,
                c = max_y - min_y + 1;

            int a, b;
            for (a = 0; a < r; a++)
                for (b = 0; b < c; b++) {
                    if (map[min_x + a][min_y + b] == '2') tmp[a][b] = '2';
                    else tmp[a][b] = '0';
                }

            for (k = 0; k < cnt; k++)
                if (check(k, min_x, min_y, r, c)) break;

            if (k == cnt) add_cluster(min_x, min_y, r, c);
        }

    for (i = 0; i < n; i++) fprintf(fout, "%s\n", map[i]);

    return 0;
}
