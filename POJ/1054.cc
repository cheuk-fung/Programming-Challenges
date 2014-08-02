/*
 *  SRC: POJ 1054
 * PROB: The Troublesome Frog
 * ALGO: DP
 * DATE: Jul 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <utility>
#include <algorithm>
using std::pair;
using std::sort;
using std::max;

const int MAXN = 5010;
const short INF = 0x3f3f;
pair<short, short> p[MAXN];
short mat[MAXN][MAXN];
short f[MAXN][MAXN];

int main()
{
    int r, c, n;
    scanf("%d%d%d", &r, &c, &n);
    for (int i = 0; i < n; i++) {
        scanf("%hd%hd", &p[i].first, &p[i].second);
        p[i].first--;
        p[i].second--;
    }
    sort(p, p + n);
    for (int i = 0; i < n; i++) {
        mat[p[i].first][p[i].second] = i + 1;
    }

    short ans = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int x, y;
            x = 2 * p[j].first - p[i].first;
            y = 2 * p[j].second - p[i].second;
            if (x < 0 || x >= r || y < 0 || y >= c) continue;
            if (!mat[x][y]) {
                f[i][j] = -INF;
                continue;
            }
            f[i][j] = f[j][mat[x][y] - 1] + 1;

            x = 2 * p[i].first - p[j].first;
            y = 2 * p[i].second - p[j].second;
            if (x < 0 || x >= r || y < 0 || y >= c) {
                ans = max(ans, f[i][j]);
            }
        }
    }

    printf("%d\n", ans ? ans + 2 : 0);

    return 0;
}

