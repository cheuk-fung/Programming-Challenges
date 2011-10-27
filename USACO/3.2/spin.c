/*
ID: os.idea1
LANG: C
TASK: spin
*/
#include <stdio.h>
#include <string.h>
FILE *fin, *fout;

int s[5], sum[5], we[5][5], wl[5][5], cir[5][360], tc[360];

int check()
{
    int i;
    for (i = 0; i < 360; i++)
	if (cir[0][i] && cir[1][i] && cir[2][i] && cir[3][i] && cir[4][i])
	    return 1;
    return 0;
}

int main()
{
    fin = fopen("spin.in", "r");
    fout = fopen("spin.out", "w");

    int i, j, k;
    for (i = 0; i < 5; i++)
    {
	fscanf(fin, "%d %d", &s[i], &sum[i]);
	for (j = 0; j < sum[i]; j++)
	{
	    fscanf(fin, "%d %d", &we[i][j], &wl[i][j]);
	    for (k = 0; k <= wl[i][j]; k++)
		cir[i][(we[i][j] + k) % 360] = i + 1;
	}
    }
	   
    for (i = 0; i < 10000; i++)
    {
	if (check())
	{
	    fprintf(fout, "%d\n", i);
	    break;
	}

	memset(tc, 0, sizeof(tc));
	for (j = 0; j < 5; j++)
	{
	    for (k = 0; k < 360; k++)
		if (cir[j][k])
		{
		    tc[(k + s[j]) % 360] = j + 1;
		    cir[j][k] = 0;
		}
	    for (k = 0; k < 360; k++)
		if (tc[k] == j + 1) cir[j][k] = j + 1;
	}
	int aaa;
	aaa = 0;
    }

    if (i == 10000) fprintf(fout, "none\n");

    fclose(fin); fclose(fout);
    return 0;
}
