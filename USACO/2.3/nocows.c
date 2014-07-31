/*
ID: os.idea1
LANG: C
TASK: nocows
*/
#include <stdio.h>

long f[100][200];

int main()
{
    FILE *fin=fopen("nocows.in","r");
    FILE *fout=fopen("nocows.out","w");

    int n, k, i, j, x;

    fscanf(fin, "%d %d", &n, &k);

    for (i = 1; i <= n; i++) f[i][1] = 1;
    for (i = 2; i <= k; i++)
        for (j = 3; j <= n; j = j + 2)
            for (x = 1; x <= j - 2; x = x + 2)
                f[i][j] = (f[i][j] + f[i - 1][x] * f[i - 1][j - 1 - x]) % 9901;

    fprintf(fout, "%ld\n", (f[k][n] + 9901 - f[k - 1][n]) % 9901);

    fclose(fin); fclose(fout);

    return 0;
}
