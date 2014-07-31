/*
ID: os.idea1
LANG: C
TASK: ratios
*/
#include <stdio.h>

FILE *fin, *fout;

int g[3], f[3][3];

int main()
{
    fin = fopen("ratios.in", "r");
    fout = fopen("ratios.out", "w");
    
    int i, j, k;
    for (i = 0; i < 3; i++) fscanf(fin, "%d", &g[i]);
    for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
	    fscanf(fin, "%d", &f[i][j]);

    int min = 100, ms[3];
    for (i = 0; i < 100; i++)
	for (j = 0; j < 100; j++)
	    for (k = 0; k < 100; k++)
	    {
		int a = i * f[0][0] + j * f[1][0] + k * f[2][0];
		if (g[0])
		{
    		    if (!a || a % g[0]) continue;
    		    a /= g[0];
		}
		else
		    if (a) continue;
		int b = i * f[0][1] + j * f[1][1] + k * f[2][1];
		if (g[1])
		{
    		    if (!b || b % g[1]) continue;
    		    b /= g[1];
		}
		else
		    if (b) continue;
		int c = i * f[0][2] + j * f[1][2] + k * f[2][2];
		if (g[2])
		{
		    if (!c || c % g[2]) continue;
    		    c /= g[2];
		}
		else
		    if (c) continue;
		if (a)
		{
		    if (!b) b = a;
		    if (!c) c = b;
		    if (a == b && b == c && a < min)
		    {
			min = a;
			ms[0] = i;
			ms[1] = j;
			ms[2] = k;
		    }
		}
		else
		{
		    if (b)
		    {
			if (!c) c = b;
			if (b == c && b < min)
			{
			    min = b;
			    ms[0] = i;
			    ms[1] = j;
			    ms[2] = k;
			}
		    }
		    else
		    {
			if (c < min)
			{
			    min = c;
			    ms[0] = i;
			    ms[1] = j;
			    ms[2] = k;
			}
		    }
		}
	    }

    if (min == 100)
	fprintf(fout, "NONE\n");
    else
	fprintf(fout, "%d %d %d %d\n", ms[0], ms[1], ms[2], min);

    fclose(fin); fclose(fout);
    return 0;
}
