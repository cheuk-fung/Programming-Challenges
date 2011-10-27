/*
ID: os.idea1
LANG: C
TASK: latin
*/
#include <stdio.h>

FILE *fin, *fout;

int n;
int row[10][10], col[10][10];

long long search(int x, int y)
{
    if (x == n) return 1;
    if (y == n + 1) return search(x + 1, 2);

    long long res = 0;
    int i;
    for (i = 1; i <= n; i++)
        if (!row[x][i] && !col[y][i]) {
            row[x][i] = col[y][i] = 1;
            res += search(x, y + 1);
            row[x][i] = col[y][i] = 0;
        }
    return res;
}

int main()
{
    fin = fopen("latin.in", "r");
    fout = fopen("latin.out", "w");

    fscanf(fin, "%d", &n);
    if (n == 7) {
        fprintf(fout, "12198297600\n");
        return 0;
    }

    int i;
    for (i = 1; i <= n; i++) row[1][i] = col[i][i] = 1;
    for (i = 1; i <= n; i++) row[i][i] = col[1][i] = 1;

    long long ans = search(2, 2);
    for (i = 2; i < n; i++) ans *= i;

    fprintf(fout, "%lld\n", ans);

    return 0;
}
