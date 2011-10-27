/*
ID: os.idea1
LANG: C
TASK: stamps
*/
#include <stdio.h>

int m, n;
int s[50];
short g[2000001], f[2000001];

int main()
{
    FILE *fin = fopen("stamps.in", "r");
    FILE *fout = fopen("stamps.out", "w");

    fscanf(fin, "%d %d", &m, &n);
    int i, j, k;
    int max = 0;
    for (i = 0; i < n; i++)
    {
	fscanf(fin, "%d", &s[i]);
	max = max > s[i] ? max : s[i];
    }

    long MAX = m * max;
    f[0] = 1;
    while (1 + 1 == 2)
    {
	int check = 0;
	for (j = 1; j <= MAX; j++)
	{
	    for (k = 0; k < n; k++)
		if (j >= s[k] && f[j - s[k]] && (g[j] > g[j - s[k]] + 1 || g[j] == 0) && g[j - s[k]] < m)
		{
		    f[j] = 1;
		    g[j] = g[j - s[k]] + 1;
		    check = 1;
		}
	}
	if (!check) break;
    }

    for (i = 1; i <= MAX; i++)
	if (!f[i]) break;

    fprintf(fout, "%d\n", i - 1);    
    
    fclose(fin); fclose(fout);
    return 0;
}
