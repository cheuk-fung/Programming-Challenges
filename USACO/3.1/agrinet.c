/*
ID: os.idea1
LANG: C
TASK: agrinet
*/
#include <stdio.h>
#include <limits.h>

long n, map[100][100], ans, lowest[100];

int main()
{
    FILE *fin = fopen("agrinet.in","r");
    FILE *fout = fopen("agrinet.out","w");

    fscanf(fin, "%ld", &n);

    long i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(fin, "%ld", &map[i][j]);

    for (i = 0; i < n; i++) lowest[i] = map[0][i];
    for (i = 0; i < n; i++)
    {
        long min = LONG_MAX, k;
        for (j = 0; j < n; j++)
            if (lowest[j] && lowest[j] < min)
            {
                min = lowest[j];
                k = j;
            }
        if (min == LONG_MAX) break;
        ans += min;
        lowest[k] = 0;
        for (j = 0; j < n; j++)
            if (map[k][j] && map[k][j] < lowest[j])
                lowest[j] = map[k][j];
    }

    fprintf(fout, "%ld\n", ans);

    fclose(fin); fclose(fout);
    return 0;
}
