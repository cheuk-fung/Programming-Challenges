/*
ID: os.idea1
LANG: C
TASK: fence
*/
#include <stdio.h>

FILE *fin, *fout;
int f, map[501][501], deg[501], cir[10000], pc;

void find_euler(int p)
{
    deg[p]--;
    int i;
    for (i = 1; i <= 500; i++)
	if (map[p][i])
	{
	    map[p][i]--; map[i][p]--;
	    deg[i]--;
	    find_euler(i);
	}
   cir[pc++] = p;
}

int main()
{
    fin = fopen("fence.in", "r");
    fout = fopen("fence.out", "w");

    fscanf(fin, "%d", &f);
    int i, a, b;
    for (i = 0; i < f; i++)
    {
	fscanf(fin, "%d %d", &a, &b);
	map[a][b]++; map[b][a]++;
	deg[a]++; deg[b]++;
    }

    for (i = 1; i <= 500; i++)
	if (deg[i] % 2) break;
    if (i == 501)
	for (i = 1; i <= 500; i++)
	    if (deg[i]) break;
    find_euler(i);

    for (i = pc; i > 0; i--)
	fprintf(fout, "%d\n", cir[i - 1]);

    fclose(fin); fclose(fout);
    return 0;
}
