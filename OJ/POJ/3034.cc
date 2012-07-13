/*
 *  SRC: POJ 3034
 * PROB: Whac-a-Mole
 * ALGO: DP
 * DATE: Jul 13, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using std::max;
using std::__gcd;

int mat[20][50][50];
int f[20][50][50];

inline int sqr(int x) { return x * x; }

int walk(int t, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2) return mat[t][x1][y1];

    int g = __gcd(abs(x2 - x1), abs(y2 - y1));
    int dx = (x2 - x1) / g;
    int dy = (y2 - y1) / g;

    int res = mat[t][x1][y1];
    do {
        x1 += dx;
        y1 += dy;
        res += mat[t][x1][y1];
    } while (x1 != x2 || y1 != y2) ;

    return res;
}

int main()
{
    int n, d, m;
    while (scanf("%d%d%d", &n, &d, &m), n || d || m) {
        memset(mat, 0, sizeof(mat));
        memset(f, 0, sizeof(f));
        n += 10;
        d *= d;

        int tmax = 0;
        for (int i = 0; i < m; i++) {
            int x, y, t;
            scanf("%d%d%d", &x, &y, &t);
            mat[t][x + 5][y + 5] = 1;
            tmax = max(tmax, t);
        }

        int ans = 0;
        for (int t = 1; t <= tmax; t++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        for (int l = 0; l < n; l++) {
                            if (sqr(k - i) + sqr(l - j) > d) continue;
                            f[t][i][j] = max(f[t][i][j], f[t - 1][k][l] + walk(t, k, l, i, j));
                        }
                    }
                    ans = max(ans, f[t][i][j]);
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

