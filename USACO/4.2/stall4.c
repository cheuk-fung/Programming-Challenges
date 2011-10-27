/*
ID: os.idea1
LANG: C
TASK: stall4
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;

long n, m, ans, cost[201][201], match[201], used[201];

long find_path(long p)
{
    long i;
    for (i = 1; i <= m; i++)
	if (cost[p][i] && !used[i])
	{
	    used[i] = 1;
	    long t = match[i];
	    match[i] = p;
	    if (t == -1 || find_path(t)) return 1;
	    match[i] = t;
	}
    return 0;
}

int main()
{
    fin = fopen("stall4.in", "r");
    fout = fopen("stall4.out", "w");

    long i, j, k;
    for (i = 1, fscanf(fin, "%ld %ld", &n, &m); i <= n; i++)
	for (j = 0, fscanf(fin, "%ld", &k); j < k; j++)
	{
	    long l;
	    fscanf(fin, "%ld", &l);
	    cost[i][l] = 1;
	}

    memset(match, -1, sizeof(match));

    for (i = 1; i <= n; i++)
    {
	memset(used, 0, sizeof(used));
	if (find_path(i)) ans++;
    }

    fprintf(fout, "%ld\n", ans);

    fclose(fin); fclose(fout);
    return 0;
}
