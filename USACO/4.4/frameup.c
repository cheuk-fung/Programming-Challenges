/*
ID: os.idea1
LANG: C
TASK: frameup
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 'Z' + 10

FILE *fin, *fout;

int H, W, sum;
char map[50][50], ans[50];
int cover[MAX_N][MAX_N], degree[MAX_N], vis[MAX_N];

struct Frame {
    int flag;
    int t, r, b, l;
} fr[MAX_N];

void topo_sort(int p)
{
    if (p == sum) {
        fprintf(fout, "%s\n", ans);
        return ;
    }

    int i, j;
    for (i = 'A'; i <= 'Z'; i++)
        if (fr[i].flag == 1 && !vis[i] && !degree[i]) {
            ans[p] = i;
            vis[i] = 1;

            for (j = 'A'; j <= 'Z'; j++)
                if (cover[j][i]) degree[j]--;
            topo_sort(p + 1);
            for (j = 'A'; j <= 'Z'; j++)
                if (cover[j][i]) degree[j]++;

            vis[i] = 0;
        }
}

int main()
{
    fin = fopen("frameup.in", "r");
    fout = fopen("frameup.out", "w");

    memset(fr, 0xff, sizeof(fr));

    fscanf(fin, "%d%d", &H, &W);

    int i, j;
    for (i = 0; i < H; i++) fscanf(fin, "%s", map[i]);

    int c;
    for (i = 0; i < H; i++)
        for (j = 0; j < W; j++) {
            if (map[i][j] == '.') continue;
            c = map[i][j];
            if (fr[c].flag == -1) {
                sum++;
                fr[c].flag = 1;
            }
            if (fr[c].t == -1 || i < fr[c].t) fr[c].t = i;
            if (fr[c].r == -1 || j > fr[c].r) fr[c].r = j;
            if (fr[c].b == -1 || i > fr[c].b) fr[c].b = i;
            if (fr[c].l == -1 || j < fr[c].l) fr[c].l = j;
        }

    for (c = 'A'; c <= 'Z'; c++)
        if (fr[c].flag == 1) {
            int t = fr[c].t, r = fr[c].r, b = fr[c].b, l = fr[c].l;
            for (j = l; j <= r; j++) {
                if (map[t][j] != '.' && map[t][j] != c) cover[map[t][j]][c] = 1;
                if (map[b][j] != '.' && map[b][j] != c) cover[map[b][j]][c] = 1;
            }
            for (i = t; i <= b; i++) {
                if (map[i][l] != '.' && map[i][l] != c) cover[map[i][l]][c] = 1;
                if (map[i][r] != '.' && map[i][r] != c) cover[map[i][r]][c] = 1;
            }
        }

    for (i = 'A'; i <= 'Z'; i++)
        for (j = 'A'; j <= 'Z'; j++)
            if (cover[i][j]) degree[i]++;

    topo_sort(0);

    return 0;
}
