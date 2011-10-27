/*
ID: os.idea1
LANG: C
TASK: kimbits
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;
int n, l, I;
int ncr[50][50];

void print(int p)
{
    int i, q = 0, s[50];
    while (p)
    {
	s[q++] = p % 2;
	p >>= 1;
    }
    if (q < n)
	for (i = q; i < n; i++)
	    fprintf(fout, "0");
    for (i = q - 1; i >= 0; i--)
	fprintf(fout, "%d", s[i]);
    fprintf(fout, "\n");
}

void init()
{
    int i, j;
    for (i = 0; i <= n; i++)
	ncr[i][0] = 1;
    for (i = 1; i <= n; i++)
	for (j = 1; j <= i; j++)
	    ncr[i][j] = ncr[i - 1][j] + ncr[i - 1][j - 1];
}

int main()
{
    fin = fopen("kimbits.in", "r");
    fout = fopen("kimbits.out", "w");

    fscanf(fin, "%d %d %d", &n, &l, &I);
    if (I != (1 << 31) - 1) I--;
    
    int tot = (1 << l) - 1;
    int i, j;
    if (tot >= I) print(I);
    else
    {
	init();
	int tmp, k = 0, pre = 0;
	for (i = n; i >= 0; i--)
	{
	    tmp = 0;
	    for (j = 1; j <= l - k; j++)
		tmp += ncr[i][j];
	    if (tmp < I)
	    {
		pre += 1 << i;
		I -= tmp + 1;
		k++;
	    }
	}
	print(pre);
    }

    fclose(fin); fclose(fout);

    return 0;
}
