/*
ID: os.idea1
LANG: C
TASK: shopping
*/
#include <stdio.h>

FILE *fin, *fout;
int s, list[100][6], cheap[100], b, need[6], ord[6], hash[1000], sum;
int f[6][6][6][6][6];

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    fin = fopen("shopping.in", "r");
    fout = fopen("shopping.out", "w");

    fscanf(fin, "%d", &s);
    int i;
    for (i = 0; i < s; i++)
    {
	int n, j;
	fscanf(fin, "%d", &n);
	for (j = 0; j < n; j++)
	{
	    int c, p;
	    fscanf(fin, "%d", &c);
	    if (hash[c]) p = hash[c];
	    else
	    {
		hash[c] = ++sum;
		p = sum;
	    }
	    fscanf(fin, "%d", &list[i][p]);
	}
	fscanf(fin, "%d", &cheap[i]);
    }
    fscanf(fin, "%d", &b);
    for (i = 0; i < b; i++)
    {
	int c, p;
	fscanf(fin, "%d", &c);
	if (hash[c]) p = hash[c];
	else
	{
	    hash[c] = ++sum;
	    p = sum;
	}
	fscanf(fin, "%d %d", &need[p], &ord[p]);
    }

    int i1, i2, i3, i4, i5;
    for (i1 = 0; i1 <= need[1]; i1++)
	for (i2 = 0; i2 <= need[2]; i2++)
	    for (i3 = 0; i3 <= need[3]; i3++)
		for (i4 = 0; i4 <= need[4]; i4++)
		    for (i5 = 0; i5 <= need[5]; i5++)
			f[i1][i2][i3][i4][i5] = i1 * ord[1] + i2 * ord[2] + i3 * ord[3] + i4 * ord[4] + i5 * ord[5];

    for (i1 = 0; i1 <= need[1]; i1++)
	for (i2 = 0; i2 <= need[2]; i2++)
	    for (i3 = 0; i3 <= need[3]; i3++)
		for (i4 = 0; i4 <= need[4]; i4++)
		    for (i5 = 0; i5 <= need[5]; i5++)
			for (i = 0; i < s; i++)
			    if (i1 - list[i][1] >= 0 && i2 - list[i][2] >= 0 && i3 - list[i][3] >= 0 && i4 - list[i][4] >= 0 && i5 - list[i][5] >= 0)
				f[i1][i2][i3][i4][i5] = min(f[i1][i2][i3][i4][i5], f[i1 - list[i][1]][i2 - list[i][2]][i3 - list[i][3]][i4 - list[i][4]][i5 - list[i][5]] + cheap[i]);

    fprintf(fout, "%d\n", f[need[1]][need[2]][need[3]][need[4]][need[5]]);

    fclose(fin); fclose(fout);
    return 0;
}
