/*
ID: os.idea1
LANG: C
TASK: fact4
*/

#include <stdio.h>

FILE *fin, *fout;

int n, p[5000], sum[5000], ans[10000];

void get_prime()
{
    int i, j;
    p[0] = 1; p[1] = 1;
    for (i = 2; i <= n; i++)
	if (!p[i])
	{
	    j = i << 1;
	    while (j <= n)
	    {
		p[j] = 1;
		j += i;
	    }
	}
    /*for (i = 2; i <= n; i++)
	if (!p[i]) printf("%d\n", i);*/
}

void divide_n()
{
    int i;
    for (i = 2; i <= n; i++)
    {
	if (p[i]) continue;
	int m = n;
	while (m > 1)
	{
	    sum[i] += m / i;
	    m /= i;
	}
    }
    sum[2] -= sum[5]; sum[5] = 0;
}

void multi()
{
    int i, j, k;
    ans[0] = 1; ans[1] = 1;
    for (i = 2; i <= n; i++)
    {
	if (!sum[i]) continue;
	for (j = 0; j < sum[i]; j++)
	{
	    ans[1] *= i;
	    k = 1;
	    while (ans[k] >= 10000)
	    {
		ans[k + 1] += ans[k] / 10000;
		ans[k] %= 10000;
	    }
	    if (k > ans[0]) ans[0] = k;
	}
    }
}

int main()
{
    fin = fopen("fact4.in", "r");
    fout = fopen("fact4.out", "w");

    fscanf(fin, "%d", &n);

    get_prime();

    divide_n();

    /*int i;
    for (i = 0; i <= n; i++)
	if (sum[i]) printf("prime:%d sum:%d\n", i, sum[i]);*/

    multi();

    fprintf(fout, "%d\n", ans[1] % 10);

    fclose(fin); fclose(fout);

    return 0;
}
