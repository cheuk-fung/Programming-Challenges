/*
ID: os.idea1
LANG: C
TASK: maze1
*/
#include <stdio.h>
#include <string.h>

int w, h, map[200][200], out[2][2], po;
int f[200][200], g[200][200], used[200][200];
int open, closed, data[20000][2];
char row_map[300][300];

void floodfill(int f[200][200], int i, int j)
{
    f[i][j] = 1;
    used[i][j] = 1;
    open = 0; closed = -1;
    data[open][0] = i; data[open][1] = j;
    while (closed <= open)
    {
        closed++;
        int m = data[closed][0], n = data[closed][1];
        if (map[m][n] & 1 && !used[m - 1][n])
        {
            f[m - 1][n] = f[m][n] + 1;
            used[m - 1][n] = 1;
            data[++open][0] = m - 1; data[open][1] = n;
        }
        if (map[m][n] & 2 && !used[m][n + 1])
        {
            f[m][n + 1] = f[m][n] + 1;
            used[m][n + 1] = 1;
            data[++open][0] = m; data[open][1] = n + 1;
        }
        if (map[m][n] & 4 && !used[m + 1][n])
        {
            f[m + 1][n] = f[m][n] + 1;
            used[m + 1][n] = 1;
            data[++open][0] = m + 1; data[open][1] = n;
        }
        if (map[m][n] & 8 && !used[m][n - 1])
        {
            f[m][n - 1] = f[m][n] + 1;
            used[m][n - 1] = 1;
            data[++open][0] = m; data[open][1] = n - 1;
        }
    }
}

int main()
{
    FILE *fin = fopen("maze1.in","r");
    FILE *fout = fopen("maze1.out","w");

    int i, j, ww, hh;
    fscanf(fin, "%d %d\n", &w, &h);
    ww = w * 2 + 1;
    hh = h * 2 + 1;
    for (i = 1; i <= hh; i++)
        for (j = 1; j <= ww + 1; j++)
            fscanf(fin, "%c", &row_map[i][j]);

//*********************************************************************************//
    /*for (i = 1; i <= hh; i++)
        for (j = 1; j <= ww + 1; j++)
            printf("%c", row_map[i][j]);*/
//*********************************************************************************//

    for (i = 2; i < hh; i = i + 2)
        for (j = 2; j < ww; j = j + 2)
        {
            if (row_map[i - 1][j] == ' ') map[i / 2][j / 2] += 1;
            if (row_map[i][j + 1] == ' ') map[i / 2][j / 2] += 2;
            if (row_map[i + 1][j] == ' ') map[i / 2][j / 2] += 4;
            if (row_map[i][j - 1] == ' ') map[i / 2][j / 2] += 8;
        }

//*********************************************************************************//
    /*for (i = 1; i <= h; i++)
    {
        for (j = 1; j <= w; j++)
            printf("%d ", map[i][j]);
        printf("\n");
    }*/
//*********************************************************************************//

    for (j = 1; j <= w; j++)
    {
        if (map[1][j] & 1)
        {
            out[po][0] = 1;
            out[po++][1] = j;
            map[1][j] -= 1;
        }
        if (map[h][j] & 4)
        {
            out[po][0] = h;
            out[po++][1] = j;
            map[h][j] -= 4;
        }
    }

    for (i = 1; i <= h; i++)
    {
        if (map[i][1] & 8)
        {
            out[po][0] = i;
            out[po++][1] = 1;
            map[i][1] -= 8;
        }
        if (map[i][w] & 2)
        {
            out[po][0] = i;
            out[po++][1] = w;
            map[i][w] -= 2;
        }
    }

//*********************************************************************************//
    /*printf("%d %d\n%d %d\n", out[0][0], out[0][1], out[1][0], out[1][1]);*/
//*********************************************************************************//

    floodfill(f, out[0][0], out[0][1]);

//*********************************************************************************//
    /*for (i = 1; i <= h; i++)
    {
        for (j = 1; j <= w; j++)
            printf("%d ", f[i][j]);
        printf("\n");
    }*/
//*********************************************************************************//

    memset(used, 0, sizeof(used));
    memset(data, 0, sizeof(data));
    floodfill(g, out[1][0], out[1][1]);

//*********************************************************************************//
    /*for (i = 1; i <= h; i++)
    {
        for (j = 1; j <= w; j++)
            printf("%d ", g[i][j]);
        printf("\n");
    }*/
//*********************************************************************************//

    int max = 0, min;
    for (i = 1; i <=h; i++)
        for (j = 1; j <= w; j++)
        {
            min = f[i][j] < g[i][j] ? f[i][j] : g[i][j];
            max = max > min ? max : min;
        }

//*********************************************************************************//
    /*printf("%d\n", max);*/
//*********************************************************************************//

    fprintf(fout, "%d\n", max);

    fclose(fin); fclose(fout);

    return 0;
}
