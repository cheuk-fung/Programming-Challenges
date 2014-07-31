/*
ID: os.idea1
LANG: C
TASK: humble
*/
#include <stdio.h>
#include <limits.h>

long k, n;
long f[100001], d[100], t[100];

void swap(long *a, long *b)
{
    long tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(long a[], long l, long r)
{
    long i = l, j = r, mid = a[(l + r) / 2];
    while (i <= j)
    {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j) swap(&a[i++], &a[j--]);
    }
    if (i < r) sort(a, i, r);
    if (j > l) sort(a, l, j);
}

int main()
{
    FILE *fin = fopen("humble.in", "r");
    FILE *fout = fopen("humble.out", "w");

    fscanf(fin, "%ld %ld", &k, &n);
    long i, j;
    for (i = 0; i < k; i++) fscanf(fin, "%ld", &d[i]);
    sort(d, 0, k - 1);
    //for (i = 0; i < k; i++) printf("%ld ", d[i]);

    f[0] = 1;
    long tot = 0;
    while (tot < n)
    {
        long min = LONG_MAX;
        for (i = 0; i < k; i++)
        {
            for (j = t[i]; j <= tot; j++)
                if (d[i] * f[j] > f[tot]) break;
            min = min < d[i] * f[j] ? min : d[i] * f[j];
            t[i] = j;
        }
        f[++tot] = min;
    }

    fprintf(fout, "%ld\n", f[n]);

    fclose(fin); fclose(fout);
    return 0;
}
