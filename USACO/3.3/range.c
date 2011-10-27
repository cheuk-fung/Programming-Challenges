/*
ID: os.idea1
LANG: C
TASK: range
*/
#include <stdio.h>

FILE *fin, *fout;
int n, f[250][250], g[250][250], sq[251], get[250][250];
char map[250][250];

int main()
{
    fin = fopen("range.in", "r");
    fout = fopen("range.out", "w");
    
    fscanf(fin, "%d\n", &n);
    int i, j, k;
    for (i = 0; i < n; i++)
    {
	for (j = 0; j < n; j++)
	{
	    fscanf(fin, "%c", &map[i][j]);
	    if (map[i][j] == '1')
		get[i][j] = 1;
	}
	fscanf(fin, "\n");
    }
    for (i = 0; i < n; i++) f[i][0] = map[i][0] - '0';
    for (j = 0; j < n; j++) g[0][j] = map[0][j] - '0';
    for (i = 0; i < n; i++)
	for (j =1; j < n; j++)
	    f[i][j] = map[i][j] == '1' ? f[i][j - 1] + 1 : 0;
    for (i = 1; i < n; i++)
	for (j = 0; j < n; j++)
	    g[i][j] = map[i][j] == '1' ? g[i - 1][j] + 1 : 0;

    for (k = 2; k <= n; k++)
	for (i = k - 1; i < n; i++)
	    for (j = k - 1; j < n; j++)
		if (get[i - 1][j - 1] >= k - 1 && f[i][j] >= k && g[i][j] >= k)
		{
		    sq[k]++;
		    get[i][j] = k;
		}

    for (k = 2; k <= n; k++)
	if (sq[k])
	    fprintf(fout, "%d %d\n", k, sq[k]);

    fclose(fin); fclose(fout);
    return 0;
}
