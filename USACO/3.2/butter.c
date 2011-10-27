/*
ID: os.idea1
LANG: C
TASK: butter
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

FILE *fin, *fout;
int n, p, c, min = LONG_MAX, cowtot[801], cost[801][801], f[1500][1500], g[1500];
int q[801], used[801], ans[801], open, closed;

int main()
{
    fin = fopen("butter.in", "r");
    fout = fopen("butter.out", "w");

    fscanf(fin, "%d %d %d", &n, &p, &c);
    int i, j, k, d;
    for (i = 0; i < n; i++)
    {
	fscanf(fin, "%d", &j);
	cowtot[j]++;
    }
    for (i = 0; i < c; i++)
    {
	fscanf(fin, "%d %d %d", &j, &k, &d);
	f[j][g[j]++] = k; cost[j][k] = d;
	f[k][g[k]++] = j; cost[k][j] = d;
    }

    for (i = 1; i <= p; i++)
	ans[i] = LONG_MAX / 2;

    for (i = 1; i <= p; i++)
    {
	open = 0; closed = -1;
	q[0] = i; used[i] = i; ans[i] = 0;
	while (closed < open)
	{
	    int u = q[(++closed) % p];
	    used[u] = 0;
	    for (j = 0; j < g[u]; j++)
		if (cost[u][f[u][j]] > 0 && cost[u][f[u][j]] + ans[u] < ans[f[u][j]])
		{
		    ans[f[u][j]] = cost[u][f[u][j]] + ans[u];
		    if (used[f[u][j]] != i)
		    {
			used[f[u][j]] = i;
			q[(++open) % p] = f[u][j];
		    }
		}
	}
	int tot = 0;
	for (j = 1; j <= p; j++)
	{
	    if (cowtot[j])
		tot += ans[j] * cowtot[j];
	    ans[j] = LONG_MAX / 2;
	}
	min = min < tot ? min : tot;
    }

    fprintf(fout, "%d\n", min);

    fclose(fin); fclose(fout);
    return 0;
}
