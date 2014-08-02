/*
 *  SRC: POJ 3368
 * PROB: Frequent values
 * ALGO: RMQ ST
 * DATE: Jul 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

const int MAXN = 100010;

int a[MAXN];
int mx[20][MAXN];

int main()
{
    int n, q;
    while (scanf("%d", &n), n) {
        scanf("%d", &q);
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            mx[0][i] = 1;
        }

        for (int i = 1; 1 << i <= n; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                int k = j + (1 << (i - 1));
                mx[i][j] = max(mx[i - 1][j], mx[i - 1][k]);
                if (a[k - 1] == a[k]) {
                    int cnt = min(j + (1 << i), upper_bound(a, a + n, a[k]) - a) - max(j, lower_bound(a, a + n, a[k]) - a);
                    mx[i][j] = max(mx[i][j], cnt);
                }
            }
        }

        for (int i = 0; i < q; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            int idx = log2(r - l + 1);
            int ans = max(mx[idx][l - 1], mx[idx][r - (1 << idx)]);
            int k = l - 1 + (1 << idx) - 1;
            int cnt = min(r, upper_bound(a, a + n, a[k]) - a) - max(l - 1, lower_bound(a, a + n, a[k]) - a);
            ans = max(ans, cnt);
            k = r - (1 << idx);
            cnt = min(r, upper_bound(a, a + n, a[k]) - a) - max(l - 1, lower_bound(a, a + n, a[k]) - a);
            ans = max(ans, cnt);
            printf("%d\n", ans);
        }
    }

    return 0;
}

