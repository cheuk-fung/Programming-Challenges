/*
ID: os.idea1
LANG: C
TASK: inflate
*/
#include <stdio.h>

long m, n;
long f[10001], v[10001], w[10001];

long max(long a, long b)
{
    return a > b ? a : b;
}

int main()
{
    FILE *fin = fopen("inflate.in","r");
    FILE *fout = fopen("inflate.out","w");

    fscanf(fin, "%ld %ld", &m, &n);
    long i, j;
    for (i = 0; i < n; i++) fscanf(fin, "%ld %ld", &v[i], &w[i]);

    for (i = 0; i < n; i++)
        for (j = w[i]; j <= m; j++)
            f[j] = max(f[j], f[j - w[i]] + v[i]);

    fprintf(fout, "%ld\n", f[m]);

    fclose(fin); fclose(fout);
    return 0;
}
