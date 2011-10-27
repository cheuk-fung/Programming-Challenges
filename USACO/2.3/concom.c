/*
ID: os.idea1
LANG: C
TASK: concom
*/
#include <stdio.h>

const int n = 101;

int f[101][101], g[101][101];

void update(int a, int b)
{
    if (g[a][b]) return;
    g[a][b] = 1;
    int i;
    for (i = 1; i <= n; i++)
        f[a][i] += f[b][i];

    for (i = 1; i <= n; i++)
        if (g[i][a]) update(i, b);

    for (i = 1; i <= n; i++)
        if (f[a][i] > 50) update(a, i);
}

void add(int a, int b, int c)
{
    int i;
    for (i = 1; i <= n; i++)
        if (g[i][a]) f[i][b] += c;

    for (i = 1; i <= n; i++)
        if (f[i][b] > 50) update(i, b);
}

int main()
{
    FILE *fin=fopen("concom.in","r");
    FILE *fout=fopen("concom.out","w");

    int t, i, j;
    fscanf(fin, "%d", &t);
    for (i = 0; i < n; i++) g[i][i] = 1;
    for (i = 0; i < t; i++)
    {
        int a, b, c;
        fscanf(fin, "%d %d %d", &a, &b, &c);
        //f[a][b] = c;
        add(a, b, c);
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (i != j && g[i][j]) fprintf(fout, "%d %d\n", i, j);

    return 0;
}

