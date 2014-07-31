/*
ID: os.idea1
LANG: C
TASK: theme
*/

#include <stdio.h>

#define MAX_N 5010

FILE *fin, *fout;

int n, a[MAX_N], f[MAX_N];

int main()
{
    fin = fopen("theme.in", "r");
    fout = fopen("theme.out", "w");

    fscanf(fin, "%d", &n);

    int i, j;
    for (i = 0; i < n; i++) fscanf(fin, "%d", a + i);

    int ans = 0;
    for (i = 0; i < n; i++)
        for (j = n - 1; j >= i + 1; j--) {
            if (a[i] - a[j] == a[i - 1] - a[j - 1]) {
                f[j] = f[j - 1];
                if (j - i > f[j - 1]) f[j]++;
                ans = f[j] > ans ? f[j] : ans;
            }
            else f[j] = 1;
        }

    fprintf(fout, "%d\n", ans >= 5 ? ans : 0);

    return 0;
}
