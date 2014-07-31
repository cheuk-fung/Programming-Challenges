/*
ID: os.idea1
LANG: C
TASK: race3
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;

long n, road[100][100], troad[100][100];
long vis[100], vis_nes[100];
long nes[100], mid[100];

void get_road(long p, long vis[])
{
    vis[p] = 1;
    long i;
    for (i = 0; i < n; i++)
	if (troad[p][i] && !vis[i]) get_road(i, vis);
}

int main()
{
    fin = fopen("race3.in", "r");
    fout = fopen("race3.out", "w");

    long tmp;
    fscanf(fin, "%ld", &tmp);
    while (tmp != -1)
    {
	while (tmp != -2)
	{
	    road[n][tmp] = 1;
	    fscanf(fin, "%ld", &tmp);
	}
	fscanf(fin, "%ld", &tmp);
	n++;
    }
    
    long i, j;
    for (i = 1; i < n - 1; i++)
    {
	memcpy(troad, road, sizeof(road));
	memset(vis, 0, sizeof(vis));
	for (j = 0; j < n; j++) troad[i][j] = 0;
	get_road(0, vis);
	if (!vis[n - 1]) nes[++nes[0]] = i;
    }
    for (i = 0; i < nes[0]; i++)
	fprintf(fout, "%ld ", nes[i]);
    fprintf(fout, "%ld\n", nes[i]);

    for (i = 1; i <= nes[0]; i++)
    {
	memcpy(troad, road, sizeof(road));
	memset(vis, 0, sizeof(vis));
	for (j = 0; j < n; j++) troad[nes[i]][j] = 0;
	get_road(0, vis);
	memcpy(troad, road, sizeof(road));
	memset(vis_nes, 0, sizeof(vis_nes));
	get_road(nes[i], vis_nes);
	for (j = 0; j < n; j++)
	    if (vis[j] && vis_nes[j] && j != nes[i]) break;
	if (j == n)
	    mid[++mid[0]] = nes[i];
    }
    for (i = 0; i < mid[0]; i++)
	fprintf(fout, "%ld ", mid[i]);
    fprintf(fout, "%ld\n", mid[i]);

    fclose(fin); fclose(fout);
    return 0;
}
