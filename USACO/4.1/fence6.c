/*
ID: os.idea1
LANG: C
TASK: fence6
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

FILE *fin, *fout;

long n, lenth[101], map[101][101], MIN = LONG_MAX;
long lowest[101], ans[101], lr[101];

int main()
{
    fin = fopen("fence6.in", "r");
    fout = fopen("fence6.out", "w");

    fscanf(fin, "%ld", &n);
    long i, j, k, l;
    for (i = 0; i < n; i++)
    {
	long t, l, r;
	fscanf(fin, "%ld", &t);
	fscanf(fin,"%ld %ld %ld", &lenth[t], &l, &r);
	for (j = 0; j < l; j++)
	{
	    fscanf(fin, "%ld", &k);
	    map[t][k] = 1;
	}
	for (j = 0; j < r; j++)
	{
	    fscanf(fin, "%ld", &k);
	    map[t][k] = 2;
	}
    }
    for (l = 1; l <= n; l++)
    {
	for (i = 1; i <= n; i++)
	{
	    ans[i] = LONG_MAX;
	    if (map[l][i] == 1) 
	    {
		lowest[i] = lenth[l] + lenth[i];
		lr[i] = map[i][l];
	    }
	    else lowest[i] = LONG_MAX;
	}
	for (i = 0; i < n - 1; i++)
	{
	    int min_tmp = LONG_MAX;
	    for (j = 1, k = 0; j <= n; j++)
		if (lowest[j] < min_tmp)
		{
		    min_tmp = lowest[j];
		    k = j;
		} 
	    if (!k) break;
	    ans[k] = lowest[k];
	    lowest[k] = LONG_MAX;
 	    for (j = 1; j <= n; j++)
  		if (map[k][j] && map[k][j] != lr[k] && ans[k] + lenth[j] < lowest[j])
		{
		    lowest[j] = ans[k] + lenth[j];
		    lr[j] = map[j][k];
		}
	}
	for (i = 1; i <= n; i++)
	    if (map[l][i] == 2 && ans[i] < MIN)
		MIN = ans[i];
    }

    fprintf(fout, "%ld\n", MIN);

    fclose(fin); fclose(fout);
    return 0;
}
