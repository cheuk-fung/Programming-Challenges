/*
ID: os.idea1
LANG: C
TASK: rockers
*/
#include <stdio.h>

FILE *fin, *fout;
int n, t, m, time[21], f[21][21][21], best;

int max(int a, int b, int c)
{
    a = a > b ? a : b;
    return a > c ? a : c;
}

int main()
{
    fin = fopen("rockers.in", "r");
    fout = fopen("rockers.out", "w");

    fscanf(fin, "%d %d %d", &n, &t, &m);

    int i, j, k;
    for (i = 1; i <= n; i++)
 	fscanf(fin, "%d", &time[i]);    

    for (i = 1; i <= n; i++)
	for (j = 1; j <= m; j++)
	    for (k = 0; k <= t; k++)
	    {
		f[i][j][k] = f[i - 1][j][k];
		if (k + time[i] <= t)
		    f[i][j][k] = max(f[i][j][k], f[i - 1][j][k + time[i]] + 1, f[i - 1][j - 1][0] + 1);
		best = max(best, f[i][j][k], 0);
	    }

    fprintf(fout, "%d\n", best);

    fclose(fin); fclose(fout);
    return 0;
}
