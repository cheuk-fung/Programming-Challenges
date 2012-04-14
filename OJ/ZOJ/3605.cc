/*
 *  SRC: ZOJ 3605
 * PROB: Find the Marble
 * ALGO: DP
 * DATE: Apr 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

using std::pair;
using std::min;

typedef pair<int, int> pii;

int n, m, k, s;
pii swapping[51];

long long f[51][51][51];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d%d%d%d", &n, &m, &k, &s);
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            swapping[i] = pii(a, b);
        }

        memset(f, 0, sizeof(f));
        f[0][0][s] = 1;
        for (int i = 1; i <= m; i++) {
            f[i][0][s] = 1;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                for (int pos = 1; pos <= n; pos++) {
                    f[i][j][pos] = f[i - 1][j][pos];
                    if (pos == swapping[i].first) {
                        f[i][j][pos] += f[i - 1][j - 1][swapping[i].second];
                    } else if (pos == swapping[i].second) {
                        f[i][j][pos] += f[i - 1][j - 1][swapping[i].first];
                    } else {
                        f[i][j][pos] += f[i - 1][j - 1][pos];
                    }
                }
            }
        }

        int ans;
        long long ans_cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (f[m][k][i] > ans_cnt) {
                ans_cnt = f[m][k][i];
                ans = i;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
