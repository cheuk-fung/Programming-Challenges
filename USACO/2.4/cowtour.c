/*
ID: os.idea1
LANG: C
TASK: cowtour
*/
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX 1e20

struct point
{
    long x, y;
}p[150];

int n, map[150][150];
double d[150][150], longest[150], dia[150], ans = MAX;

double max(double a, double b)
{
    return a > b ? a : b;
}

double min(double a, double b)
{
    return a < b ? a : b;
}

double dist(int i, int j)
{
    return sqrt(pow(p[i].x - p[j].x, 2) + pow(p[i].y - p[j].y, 2));
}

int main()
{
    FILE *fin = fopen("cowtour.in","r");
    FILE *fout = fopen("cowtour.out","w");

    fscanf(fin, "%d", &n);

    int i, j, k;

    for (i = 0; i < n; i++)
        fscanf(fin, "%ld %ld", &p[i].x, &p[i].y);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            char c;
            fscanf(fin, "%c", &c);
            if (c == '\n') fscanf(fin, "%c", &c);
            map[i][j] = (int)c - (int)'0';
            if (map[i][j])
                d[i][j] = dist(i, j);
            else d[i][j] = MAX;
        }

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
        {
            if (i == k) continue;
            for (j = 0; j < n; j++)
            {
                if (j == i || j == k) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (d[i][j] < MAX)
                longest[i] = max(longest[i], d[i][j]);

    for (i = 0; i < n; i++)
    {
        dia[i] = longest[i];
        for (j = 0; j < n; j++)
            if (d[i][j] < MAX)
                dia[i] = max(dia[i], longest[j]);
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (d[i][j] == MAX && i != j)
            {
                double tmp = max(dia[i], dia[j]);
                tmp = max(tmp, longest[i] + dist(i, j) + longest[j]);
                ans = min(ans, tmp);
            }

    fprintf(fout, "%.6f\n", ans);

    fclose(fin); fclose(fout);

    return 0;
}
