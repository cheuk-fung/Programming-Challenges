/*
ID: os.idea1
LANG: C
TASK: game1
*/
#include <stdio.h>

FILE *fin, *fout;
int n, d[100], g[100][100];

struct fun
{
    int f, l;
} f[100][100];

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    fin = fopen("game1.in", "r");
    fout = fopen("game1.out", "w");

    fscanf(fin, "%d", &n);
    int i, j, l;
    for (i = 0; i < n; i++)
    {
	fscanf(fin, "%d", &d[i]);
	g[i][i] = d[i];
	f[i][i].f = d[i]; f[i][i].l = 0;
    }

    for (i = 0; i < n; i++)
	for (j = i + 1; j < n; j++)
	    g[i][j] = g[i][j - 1] + d[j];

    for (l = 2; l <= n; l++)
	for (i = 0; i < n; i++)
	{
	    j = i + l - 1;
	    if (j >= n) break;
	    f[i][j].f = max(d[i] + f[i + 1][j].l, f[i][j - 1].l + d[j]);
	    f[i][j].l = g[i][j] - f[i][j].f;
	}

    fprintf(fout, "%d %d\n", f[0][n - 1].f, f[0][n - 1].l);    

    fclose(fin); fclose(fout);
    return 0;
}
