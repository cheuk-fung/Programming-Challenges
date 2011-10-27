/*
ID: os.idea1
LANG: C
TASK: milk4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin, *fout;

int n, m;
int v[111];
int best = 0x3fffffff, now[111], ans[111];

int cmp(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

int check()
{
    int i;
    for (i = best - 1; i >= 0; i--)
        if (ans[i] != now[i])
            return ans[i] - now[i];
    return -1;
}

void dfs(int prev, int p, int q)
{
    if (p > best) return ;
    if (q == n) {
        if (p < best || (p == best && check() > 0)) {
            memcpy(ans, now, sizeof(int) * p);
            best = p;
        }
        return ;
    }

    int i, j;
    for (i = prev - 1; i >= 0; i--) {
        now[p] = v[i];
        j = (n - q) / v[i];
        while (j) dfs(i, p + 1, q + v[i] * j--);
    }
}

int main()
{
    fin = fopen("milk4.in", "r");
    fout = fopen("milk4.out", "w");

    fscanf(fin, "%d%d", &n, &m);

    int i;
    for (i = 0; i < m; i++) fscanf(fin, "%d", v + i);
    qsort(v, m, sizeof(int), cmp);

    dfs(m, 0, 0);

    fprintf(fout, "%d", best);
    for (i = best - 1; i >= 0; i--) fprintf(fout, " %d", ans[i]);
    fputc(10, fout);

    return 0;
}
