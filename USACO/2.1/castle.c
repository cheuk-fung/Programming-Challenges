/*
ID: os.idea1
LANG: C
TASK: castle
*/
#include <stdio.h>
#include <string.h>

int n, m, sum, max;
int search[50][50];

struct point
{
    int W, N, E, S;
} room[50][50];

int MAX(int a, int b)
{
    return a > b ? a : b;
}

int floodfill(int a, int b)
{
    if (search[a][b]) return 0;
    search[a][b] = 1;
    int ans = 1;
    if (!room[a][b].W && b >= 1) ans += floodfill(a, b - 1);
    if (!room[a][b].N && a >= 1) ans += floodfill(a - 1, b);
    if (!room[a][b].E && b + 1 < m) ans += floodfill(a, b + 1);
    if (!room[a][b].S && a + 1 < n) ans += floodfill(a + 1, b);
    return ans;
}

int main()
{
    FILE *fin=fopen("castle.in","r");
    FILE *fout=fopen("castle.out","w");

    fscanf(fin, "%d %d", &m, &n);

    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            int tmp;
            fscanf(fin, "%d", &tmp);
            room[i][j].W = tmp & 1;
            room[i][j].N = tmp & 2;
            room[i][j].E = tmp & 4;
            room[i][j].S = tmp & 8;
        }

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (!search[i][j])
            {
                sum++;
                max = MAX(max, floodfill(i, j));
            }

    fprintf(fout, "%d\n%d\n", sum, max);

    int mi, mj;
    char dir;
    for (j = 0; j < m; j++)
        for (i = n - 1; i >= 0; i--)
        {
            if (room[i][j].W)
            {
                room[i][j].W = 0;
                memset(search, 0, sizeof(search));
                int tmp = MAX(max, floodfill(i, j));
                if (tmp > max)
                {
                    max = tmp;
                    mi = i; mj = j;
                    dir = 'W';
                }
                room[i][j].W = 1;
            }
            if (room[i][j].N)
            {
                room[i][j].N = 0;
                memset(search, 0, sizeof(search));
                int tmp = MAX(max, floodfill(i, j));
                if (tmp > max)
                {
                    max = tmp;
                    mi = i; mj = j;
                    dir = 'N';
                }
                room[i][j].N = 1;
            }
            if (room[i][j].E)
            {
                room[i][j].E = 0;
                memset(search, 0, sizeof(search));
                int tmp = MAX(max, floodfill(i, j));
                if (tmp > max)
                {
                    max = tmp;
                    mi = i; mj = j;
                    dir = 'E';
                }
                room[i][j].E = 1;
            }
            if (room[i][j].S)
            {
                room[i][j].S = 0;
                memset(search, 0, sizeof(search));
                int tmp = MAX(max, floodfill(i, j));
                if (tmp > max)
                {
                    max = tmp;
                    mi = i; mj = j;
                    dir = 'S';
                }
                room[i][j].S = 1;
            }
        }

    fprintf(fout, "%d\n%d %d %c\n", max, mi + 1, mj + 1, dir);

    fclose(fin);

    return 0;
}
