/*
ID: os.idea1
LANG: C
TASK: bigbrn
*/
#include <stdio.h>

FILE *fin, *fout;

int n, t;
int map[1010][1010];
int row[1010][1010];

int check(int size)
{
    int i, j;
    for (j = 1; j <= n; j++) {
        int cnt = 0,
            min = 0x3fffffff;
        for (i = 1; i <= n; i++) {
            if (row[i][j] >= size) cnt++;
            else {
                cnt = 0;
                min = row[i][j] < min ? row[i][j] : min;
            }

            if (cnt >= size) return 1;
        }

        j += min;
    }
    return 0;
}

int solve()
{
    int left = 1, right = n;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    return left;
}

int main()
{
    fin = fopen("bigbrn.in", "r");
    fout = fopen("bigbrn.out", "w");

    fscanf(fin, "%d%d", &n, &t);
    int i, j;
    while (t--) {
        fscanf(fin, "%d%d", &i, &j);
        map[i][j] = 1;
    }

    for (i = n; i > 0; i--)
        for (j = n; j > 0; j--)
            if (!map[i][j])
                row[i][j] = row[i][j + 1] + 1;

    int ans = solve();
    fprintf(fout, "%d\n", ans);

    return 0;
}
