/*
ID: os.idea1
LANG: C
TASK: job
*/
#include <stdio.h>
#include <limits.h>

FILE *fin, *fout;

long n, m1, m2, t1[30], t2[30], d1[30], d2[30], a1[1000], a2[1000];

int main()
{
    fin = fopen("job.in", "r");
    fout = fopen("job.out", "w");

    fscanf(fin, "%ld %ld %ld", &n, &m1, &m2);
    long i;
    for (i = 0; i < m1; i++) fscanf(fin, "%ld", &t1[i]);
    for (i = 0; i < m2; i++) fscanf(fin, "%ld", &t2[i]);

    long min, ans1 = 0, ans2 = 0, j, k;
    for (i = 0; i < n; i++)
    {
	min = LONG_MAX;
	for (j = 0; j < m1; j++)
	    if (d1[j] + t1[j] < min)
	    {
		min = d1[j] + t1[j];
		k = j;
	    }
	d1[k] += t1[k];
	a1[i] = d1[k];
	if (d1[k] > ans1) ans1 = d1[k];

	min = LONG_MAX;
	for (j = 0; j< m2; j++)
	    if (d2[j] + t2[j] < min)
	    {
		min = d2[j] + t2[j];
		k = j;
	    }
	d2[k] += t2[k];
	a2[i] = d2[k];
    }

    for (i = 0; i < n; i++)
	if (a1[i] + a2[n - i - 1] > ans2)
	    ans2 = a1[i] + a2[n - i - 1];

    fprintf(fout, "%ld %ld\n", ans1, ans2);

    fclose(fin); fclose(fout);
    return 0;
}
