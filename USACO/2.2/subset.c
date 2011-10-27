/*
ID: os.idea1
LANG: C
TASK: subset
*/
#include <stdio.h>

int n;
long tot;
long f[50][2000];

void dp()
{
    int i, j;
    for (i = 1; i <= n; i++) f[i][0] = 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= tot; j++)
        {
            if (i <= j)
                f[i][j] = f[i - 1][j] + f[i - 1][j - i];
            else f[i][j] = f[i - 1][j];
        }
}

int main()
{
    FILE *fin=fopen("subset.in","r");
    FILE *fout=fopen("subset.out","w");

    fscanf(fin, "%d", &n);
    tot = (1 + n) * n / 2;
    if (tot % 2) fprintf(fout, "0\n");
    else
    {
        dp();
        fprintf(fout, "%ld\n", f[n][tot / 2]);
    }

    fclose(fin); fclose(fout);

    return 0;
}
