/*
ID: os.idea1
LANG: C
TASK: holstein
*/
#include <stdio.h>

int n, v[100], m, g[100][100], ans[100], select[100];

int GetIt(int p, int q, int t)
{
    if (p == q)
    {
        int i;
        for (i = 0; i < n; i++)
            if (ans[i] < v[i]) return 0;
        return 1;
    }
    int i, j;
    for (i = t; i < m; i++)
    {
        select[q] = i;
        for (j = 0; j < n; j++) ans[j] += g[i][j];
        if (GetIt(p, q + 1, i + 1)) return 1;
        for (j = 0; j < n; j++) ans[j] -= g[i][j];
    }
    return 0;
}

int main()
{
    FILE *fin=fopen("holstein.in", "r");
    FILE *fout=fopen("holstein.out", "w");

    int i, j;
    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) fscanf(fin, "%d", &v[i]);
    fscanf(fin, "%d", &m);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++) fscanf(fin, "%d", &g[i][j]);

    int p = 1;

    while (!GetIt(p, 0, 0)) p++;

    fprintf(fout, "%d", p);
    for (j = 0; j < p; j++) fprintf(fout, " %d", select[j] + 1);
    fprintf(fout, "\n");

    fclose(fin); fclose(fout);

    return 0;
}
