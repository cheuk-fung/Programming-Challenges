/*
ID: os.idea1
LANG: C
TASK: money
*/
#include <stdio.h>

long long f[25][10001];

int main()
{
    FILE *fin=fopen("money.in","r");
    FILE *fout=fopen("money.out","w");

    long v, n, m[25], i, j;
    fscanf(fin, "%ld %ld", &v, &n);
    for (i = 0; i < v; i++) fscanf(fin, "%ld", &m[i]);

    for (i = 0; i < v; i++) f[i][m[i]] = 1;
    for (i = 0; i < v; i++)
        for (j = 1; j <= n; j++)
        {
            if (i > 0)
            {
                if (j > m[i]) f[i][j] += f[i - 1][j] + f[i][j - m[i]];
                else f[i][j] += f[i - 1][j];
            }
            else if (j > m[i]) f[i][j] += f[i][j - m[i]];
        }

    fprintf(fout, "%lld\n", f[v - 1][n]);

    fclose(fin); fclose(fout);

    return 0;
}

