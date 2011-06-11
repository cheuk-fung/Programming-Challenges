/*
 *  SRC: POJ 3467
 * PROB: Cross Counting
 * ALGO: NULL
 * DATE: May 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int n, m, c, q;
int map[110][110], cnt[110];

int count(int i, int j)
{
    int res = 0;
    for (int k = 1; ; k++) {
        if (i - k < 0 || i + k == n || j - k < 0 || j + k == m) break;
        if (map[i - k][j] != map[i][j]) break;
        if (map[i + k][j] != map[i][j]) break;
        if (map[i][j - k] != map[i][j]) break;
        if (map[i][j + k] != map[i][j]) break;
        res++;
    }
    return res;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &c, &q);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", map[i] + j);

    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            cnt[map[i][j]] += count(i, j);

    while (q--) {
        getchar();
        char c = getchar();
        if (c == 'Q') {
            int color;
            scanf("%d", &color);
            printf("%d\n", cnt[color]);
        }
        else {
            int x, y, color;
            scanf("%d%d%d", &x, &y, &color);
            x--; y--;
            for (int i = 0; i < n; i++) {
                if (i == x) continue;
                cnt[map[i][y]] -= count(i, y);
            }
            for (int j = 0; j < m; j++) {
                if (j == y) continue;
                cnt[map[x][j]] -= count(x, j);
            }
            cnt[map[x][y]] -= count(x, y);
            map[x][y] = color;
            for (int i = 0; i < n; i++) {
                if (i == x) continue;
                cnt[map[i][y]] += count(i, y);
            }
            for (int j = 0; j < m; j++) {
                if (j == y) continue;
                cnt[map[x][j]] += count(x, j);
            }
            cnt[map[x][y]] += count(x, y);
        }
    }

    return 0;
}

