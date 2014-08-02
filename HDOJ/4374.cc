/*
 *  SRC: HDO 4374
 * PROB: One hundred layer
 * ALGO: DP
 * DATE: Aug 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 110;
const int MAXM = 10010;

int a[MAXN][MAXM], sum[MAXN][MAXM];
int f[MAXN][MAXM], que[MAXM];

int main()
{
    int n, m, x, t;
    while (~scanf("%d%d%d%d", &n, &m, &x, &t)) {
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
                sum[i][j] = sum[i][j - 1] + a[i][j];
            }
        }

        for (int i = 1; i <= m; i++) f[0][i] = -INF;
        f[0][x] = 0;
        for (int i = 1; i <= n; i++) {
            int head = 0, tail = 0;
            for (int j = 1; j <= m; j++) {
                while (head < tail && j - que[head] > t) head++;
                while (head < tail && f[i - 1][que[tail - 1]] + sum[i - 1][j] - sum[i - 1][que[tail - 1] - 1] < f[i - 1][j] + a[i - 1][j]) tail--;
                que[tail++] = j;
                f[i][j] = f[i - 1][que[head]] + sum[i - 1][j] - sum[i - 1][que[head] - 1];
            }

            head = 0, tail = 0;
            for (int j = m; j >= 1; j--) {
                while (head < tail && que[head] - j > t) head++;
                while (head < tail && f[i - 1][que[tail - 1]] + sum[i - 1][que[tail - 1]] - sum[i - 1][j - 1] < f[i - 1][j] + a[i - 1][j]) tail--;
                que[tail++] = j;
                f[i][j] = max(f[i][j], f[i - 1][que[head]] + sum[i - 1][que[head]] - sum[i - 1][j - 1]);
            }
        }

        int ans = 0;
        for (int i = 1; i <= m; i++) ans = max(ans, f[n][i]);
        printf("%d\n", ans);
    }

    return 0;
}


