/*
ID: os.idea1
LANG: C
TASK: buylow
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;

long n, d[5001], f[5001], link[5001], lg[5001];
long g[5001][501];

void add(long a, long b)
{
    long i;
    lg[a] = lg[a] > lg[b] ? lg[a] : lg[b];
    for (i = 0; i < lg[a]; i++)
	g[a][i] += g[b][i];
    for (i = 0; i < lg[a]; i++)
	if (g[a][i] >= 10000)
	{
	    g[a][i + 1]++;
	    g[a][i] -= 10000;
	}
    if (g[a][lg[a]]) lg[a]++;
}

int main()
{
    fin = fopen("buylow.in", "r");
    fout = fopen("buylow.out", "w");

    fscanf(fin, "%ld", &n);
    long i, j;
    for (i = 0; i < n; i++) 
    {
	fscanf(fin, "%ld", &d[i]);
	g[i][lg[i]++] = 1;
    }

    for (i = 0; i <= n; i++)
	for (j = i + 1; j <=n; j++)
	    if (d[i] == d[j])
	    {
		link[i] = j;
		break;
	    }
    for (i = 1; i <= n; i++)
	for (j = i - 1; j >= 0; j--)
	    if (d[j] > d[i])
	    {
		if (f[j] >= f[i])
		{
		    f[i] = f[j] + 1;
		    //g[i] = g[j];
		    memcpy(g[i], g[j], sizeof(g[j]));
		    lg[i] = lg[j];
		}
		else 
		    if (f[j] + 1 == f[i] && (!link[j] || link[j] > i))
			add(i, j); // g[i] += g[j];
	    }

    fprintf(fout, "%ld %ld", f[n], g[n][lg[n] - 1]);
    for (i = lg[n] - 2; i >= 0; i--)
    {
	if (g[n][i] < 1000) fprintf(fout, "0");
	if (g[n][i] < 100) fprintf(fout,"0");
	if (g[n][i] < 10) fprintf(fout, "0");
	fprintf(fout, "%ld", g[n][i]);
    }
    fprintf(fout, "\n");

    fclose(fin); fclose(fout);
    return 0;
}
